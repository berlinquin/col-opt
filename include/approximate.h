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
   {
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
   //printf("elementIndex: %d, numberElements: %d\n", elementIndex, numberElements);
   assert(elementIndex == (TABLE_ROWS*TABLE_COLS));
   }
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

   free(rows);
   free(length);
   free(start);
   return std::vector<int> {};
}
