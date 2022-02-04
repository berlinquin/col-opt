#include "colopt.h"
#include <cmath>

inline int max(int a, int b)
{
   return (a > b) ? a : b;
}

int cost(const table_type& table, const std::vector<int>& widths)
{
   int table_length = 0;

   const int ROWS = table.shape()[0];
   const int COLS = table.shape()[1];

   for (table_index i = 0; i < ROWS; i++)
   {
      int row_length = 0;
      for (table_index j = 0; j < COLS; j++)
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
