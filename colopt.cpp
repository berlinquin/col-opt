#include "colopt.h"
#include <cmath>
#include "combination.h"

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

void optimize(const table_type& table, int width)
{
   printf("optimize()\n");
   
   const int ROWS = table.shape()[0];
   const int COLS = table.shape()[1];

   combination_generator cg(width-1, COLS-1);
   int i = 0;
   while (cg.has_next())
   {
      std::vector<int> out = cg.next();
      //printf("[%d, %d, %d]\n", out[0], out[1], out[2]);
      i++;
   }
   printf("There are %d combinations\n", i);
}

