#include <iostream>

#include "parser.h"
#include "Matrix.h"

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      std::cout << "ERROR: Must pass filename as an argument" << std::endl;
      return 1;
   }

   // If argv has a filename, open that for reading
   // Otherwise, read from stdin
   array_type *cell_lengths;
   bool success = parse_csv(argv[1], &cell_lengths);
   if (!success)
   {
      return 1;
   }

   printf("cell_lengths has %d dimensions\n", cell_lengths->num_dimensions());
   const int ROWS = cell_lengths->shape()[0];
   const int COLS = cell_lengths->shape()[1];
   printf("  %d x %d\n", ROWS, COLS);

   for (index i = 0; i < ROWS; i++)
   {
      for (index j = 0; j < COLS; j++)
      {
         printf("%d\t", (*cell_lengths)[i][j]);
      }
      printf("\n");
   }
   return 0;
}
