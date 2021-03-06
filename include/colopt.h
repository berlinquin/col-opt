#include <vector>
#include <cmath>
#include "combination.h"

// Return the cost of the table
// as its length in lines for the given widths
template<typename T>
int cost(const T& table, const std::vector<int>& widths);

// Optimize the table to fit in the given width,
// printing out optimal width and total lines to stdout
template<typename T>
std::vector<int> optimize(const T& table, int width);



// Helper function
inline int max(int a, int b)
{
   return (a > b) ? a : b;
}

// cost() implementation
template<typename T>
int cost(const T& table, const std::vector<int>& widths)
{
   int table_length = 0;

   const int ROWS = table.shape()[0];
   const int COLS = table.shape()[1];

   // Type alias for the table index type
   using index_type = typename T::index;

   for (index_type i = 0; i < ROWS; i++)
   {
      int row_length = 0;
      for (index_type j = 0; j < COLS; j++)
      {
         // Divide cell length by the width assigned
         double d = (1.0 * table[i][j]) / widths[j];
         // Round up to the nearest line
         int cell_length = std::ceil(d);
         // Update row length with the max cell length in the row
         row_length = max(row_length, cell_length);
      }
      table_length += row_length;
   }
   return table_length;
}

// optimize() implementation
template<typename T>
std::vector<int> optimize(const T& table, int width)
{
   printf("optimize()\n");

   const int ROWS = table.shape()[0];
   const int COLS = table.shape()[1];

   int usable_width = width - COLS + 1;

   printf("Given width %d and table with %d columns, "
         "usable width is %d\n", width, COLS, usable_width);
   // vector of size COLS
   std::vector<int> widths(COLS);

   combination_generator::simple_vector cg(usable_width-1, COLS-1);
   int i = 0;
   int min_cost = INT_MAX;
   std::vector<int> min_widths;
   while (cg.has_next())
   {
      // cg.next() returns indices in range [0, usable_width)
      std::vector<int> dividers = cg.next();
      // Calculate the width of the first column manually
      widths[0] = dividers[0] + 1;
      // Count how much width has been assigned
      int accumulated_width = widths[0];
      for (int i = 1; i < COLS-1; i++)
      {
         widths[i] = dividers[i] - dividers[i-1];
         accumulated_width += widths[i];
      }
      // Calculate the width of the last column manually
      widths[COLS-1] = usable_width - accumulated_width;

      /*
      printf("dividers:\n");
      printf("[");
      for (int i = 0; i < dividers.size(); i++)
      {
         printf("%d ", dividers[i]);
      }
      printf("]\n");

      // print out widths
      printf("widths:\n");
      printf("[");
      for (int i = 0; i < widths.size(); i++)
      {
         printf("%d ", widths[i]);
      }
      printf("]\n");
      */

      int c = cost(table, widths);
      if (c < min_cost)
      {
         min_cost = c;
         min_widths = widths;
      }

      i++;
   }

   printf("There are %d combinations\n", i);

   printf("Minimum cost of %d given by widths:\n", min_cost);
   // print out widths
   printf("[");
   for (int i = 0; i < min_widths.size(); i++)
   {
      printf("%d ", min_widths[i]);
   }
   printf("]\n");
   // print out the length of each line in the table
   using index_type = typename T::index;
   for (index_type i = 0; i < ROWS; i++)
   {
      int row_length = 0;
      printf("row %ld: [", i);
      for (index_type j = 0; j < COLS; j++)
      {
         // Divide cell length by the width assigned
         double d = (1.0 * table[i][j]) / widths[j];
         // Round up to the nearest line
         int cell_length = std::ceil(d);
         // Update row length with the max cell length in the row
         row_length = max(row_length, cell_length);
         printf("%d, ", table[i][j]);
      }
      printf("], %d\n", row_length);
   }
   return min_widths;
}
