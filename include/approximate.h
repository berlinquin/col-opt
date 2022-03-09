#include <cassert>
#include <numeric>
#include <coin/ClpSimplex.hpp>
#include <coin/CoinHelperFunctions.hpp>

// Approximate the optimal solution with linear programming
template<typename T>
std::vector<int> approximate(const T& table, int width);



template<typename T>
std::vector<int> approximate(const T& table, int width)
{
   printf("approximate()\n");

   const int TABLE_ROWS = table.shape()[0];
   const int TABLE_COLS = table.shape()[1];

   // Establish the size of the problem matrix

   // For each row in table, there will be COLS constraints.
   // There is one additional constraint placed on widths.
   const int numberRows = (TABLE_ROWS * TABLE_COLS) + 1;
   // There will be a variable for each row in table,
   // and one for each column
   const int numberColumns = TABLE_ROWS + TABLE_COLS;
   // For each of the row constraints,
   // there are 2 coefficients on variables.
   // For the width constraint, there is a coefficient for each column in table.
   const int numberElements = (TABLE_ROWS * TABLE_COLS * 2) + TABLE_COLS;

   // Construct the problem matrix in column-major order

   // start holds the starting index of each column
   // (Notice that start has numberColumns+1 items, the last index is invalid)
   CoinBigIndex *start = (CoinBigIndex*)calloc(numberColumns+1, sizeof(CoinBigIndex));
   start[0] = 0;
   int i;
   // The first TABLE_ROWS columns hold TABLE_COLS elements each
   // (Notice the loop guard: set TABLE_ROWS elements total)
   for (i = 1; i <= TABLE_ROWS; i++)
   {
      start[i] = start[i-1] + TABLE_COLS;
   }
   // The next TABLE_COLS columns hold (TABLE_ROWS + 1) elements each
   // (Notice the loop guard: set TABLE_COLS elements total)
   for (; i < numberColumns+1; i++)
   {
      start[i] = start[i-1] + TABLE_ROWS + 1;
   }
   // Sanity check that start was initialized correctly
   assert(start[numberColumns] == numberElements);

   // length holds the number of elements in each column
   int *length = (int*)calloc(numberColumns, sizeof(int));
   // Construct length with values from start
   for (int i = 0; i < numberColumns; i++)
   {
      length[i] = start[i+1] - start[i];
   }
   // Sanity check that total length is the sum
   assert(std::reduce(length, length+numberColumns) == numberElements);

   // For each element, rows holds the element's row index
   // (i.e. which row it belongs to)
   int *rows = (int*)calloc(numberElements, sizeof(int));
   // Process first TABLE_ROWS columns
   int elementIndex = 0;
   // Start at one since the row constraints start at the second row
   int rowIndex = 1;
   // Set the first TABLE_ROWS*TABLE_COLS elements
   for (int i = 0; i < TABLE_ROWS; i++)
   {
      for (int j = 0; j < TABLE_COLS; j++)
      {
         rows[elementIndex] = rowIndex;
         ++elementIndex;
         ++rowIndex;
      }
   }
   // Sanity check
   assert(rowIndex == numberRows);
   assert(elementIndex == (TABLE_ROWS*TABLE_COLS));
   // Set the remaining TABLE_ROWS*TABLE_COLS + TABLE_COLS elements
   for (int i = 0; i < TABLE_COLS; i++)
   {
      // There's always an entry in the first row for the weight constraint
      rows[elementIndex] = 0;
      ++elementIndex;
      // Offset row index from the the first row
      // (careful, this hides declaration in parent scope)
      int rowIndex = 1 + i;
      for (int j = 0; j < TABLE_ROWS; j++)
      {
         rows[elementIndex] = rowIndex;
         ++elementIndex;
         rowIndex += TABLE_COLS;
      }
   }
   // Sanity check
   printf("elementIndex: %d, numberElements: %d\n", elementIndex, numberElements);
   assert(elementIndex == numberElements);

   // Elements holds the coefficient on each variable
   double *elements = (double*)calloc(numberElements, sizeof(double));
   elementIndex = 0;
   for (int i = 0; i < TABLE_ROWS; i++)
   {
      for (int j = 0; j < TABLE_COLS; j++)
      {
         elements[elementIndex] = 1;
         ++elementIndex;
      }
   }
   // Sanity check
   assert(elementIndex == (TABLE_ROWS*TABLE_COLS));
   for (int i = 0; i < TABLE_COLS; i++)
   {
      elements[elementIndex] = 1;
      ++elementIndex;
      // These indices track positions in the row-major table argument
      int tableRow = 0;
      int tableCol = i;
      for (int i = 0; i < TABLE_ROWS; i++)
      {
         double inverse;
         int cellLen = table[tableRow][tableCol];
         if (cellLen != 0)
         {
            inverse = -1.0 / cellLen;
         }
         else
         {
            inverse = 0.0;
         }
         elements[elementIndex] = inverse;
         ++elementIndex;
         ++tableRow;
      }
   }
   // Sanity check
   assert(elementIndex == numberElements);

   // Create a packed (sparse) matrix from the given arrays
   CoinPackedMatrix matrix(true, numberRows, numberColumns, numberElements,
         elements, rows, start, length);

   // Initialize the parameters to the model

   // objective holds array of coefficients for all variables in the model.
   // Linear programming will maximize or minimize the
   // dot product of this array with all the variables in the model.
   double *objective = (double*)calloc(numberColumns, sizeof(double));
   // Initialize the first TABLE_ROWS coefficients to one,
   // and leave the remaining TABLE_COLS coefficients to be zero
   for (int i = 0; i < TABLE_ROWS; i++)
   {
      objective[i] = 1.0;
   }

   double *rowLower = (double*)calloc(numberRows, sizeof(double));
   // Only the first constraint has a lower bound
   rowLower[0] = width;
   for (int i = 1; i < numberRows; i++)
   {
      rowLower[i] = -COIN_DBL_MAX;
   }

   double *rowUpper = (double*)calloc(numberRows, sizeof(double));
   // Only the first constraint has a non-zero upper bound.
   // All other upper bounds are zero.
   rowUpper[0] = width;

   double *colLower = (double*)calloc(numberColumns, sizeof(double));
   for (int i = 0; i < TABLE_ROWS; i++)
   {
      // The first TABLE_ROWS variables do not have a lower bound
      colLower[i] = -COIN_DBL_MAX;
   }
   for (int i = 0; i < TABLE_COLS; i++)
   {
      // All of the width variables must be at least one.
      colLower[TABLE_ROWS+i] = 1.0;
   }

   double *colUpper = (double*)calloc(numberColumns, sizeof(double));
   for (int i = 0; i < numberColumns; i++)
   {
      // The first TABLE_ROWS variables do not have an upper bound.
      // The following TABLE_COLS variables do have an upper bound,
      // but this is enforced by the first constraint in rowLower and rowUpper.
      colUpper[i] = COIN_DBL_MAX;
   }


   // print out the column lower bounds
   printf("colLower: [");
   for (int i = 0; i < numberColumns; i++)
   {
      printf("%0.2e, ", colLower[i]);
   }
   printf("]\n");
   // print out the generated matrix
   for (int i = 0; i < numberRows; i++)
   {
      printf("row %.3d: %0.2e <= [", i, rowLower[i]);
      for (int j = 0; j < numberColumns; j++)
      {
         double coeff = matrix.getCoefficient(i, j);
         printf("%0.4f, ", coeff);
      }
      printf("] <= %0.4f\n", rowUpper[i]);
   }
   printf("colUpper: [");
   for (int i = 0; i < numberColumns; i++)
   {
      printf("%0.2e, ", colUpper[i]);
   }
   printf("]\n");


   // Load problem into a Simplex model
   ClpSimplex model;
   model.loadProblem(matrix, colLower, colUpper, objective,
         rowLower, rowUpper);

   // Looks like Clp tries to minimize by default,
   // adjusting the objective scale causes it to maximize instead
   model.setObjectiveScale(-1.0);

   // Solve
   printf("model.initialSolve()\n");
   model.initialSolve();
   // Check the solution returned by the model
   const double *solution = model.primalColumnSolution();
   for (int i = 0; i < numberColumns; i++)
   {
      if (solution[i])
      {
         printf("Column %d has value %g\n", i, solution[i]);
      }
      else
      {
         printf("Column %d has NO solution: %g\n", i, solution[i]);
      }
   }

   printf("model.primal(1)\n");
   model.primal(1);
   // Check the solution returned by the model
   solution = model.primalColumnSolution();
   for (int i = 0; i < numberColumns; i++)
   {
      if (solution[i])
      {
         printf("Column %d has value %g\n", i, solution[i]);
      }
      else
      {
         printf("Column %d has NO solution: %g\n", i, solution[i]);
      }
   }

   printf("model.dual()\n");
   model.dual();
   // Check the solution returned by the model
   solution = model.primalColumnSolution();
   for (int i = 0; i < numberColumns; i++)
   {
      if (solution[i])
      {
         printf("Column %d has value %g\n", i, solution[i]);
      }
      else
      {
         printf("Column %d has NO solution: %g\n", i, solution[i]);
      }
   }


   free(colUpper);
   free(colLower);
   free(rowUpper);
   free(rowLower);
   free(objective);
   free(elements);
   free(rows);
   free(length);
   free(start);
   return std::vector<int> {};
}
