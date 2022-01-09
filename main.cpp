#include <iostream>

#include "parser.h"
#include "Matrix.h"

int main(int argc, char *argv[])
{
   // argv[1] must hold the filename of the csv file to open
   if (argc < 2)
   {
      std::cout << "ERROR: Must pass filename as an argument" << std::endl;
      return 1;
   }

   array_type *cell_lengths;
   bool success = parse_csv(argv[1], &cell_lengths);
   if (!success)
   {
      return 1;
   }

   // array_type has two dimensions by definition
   const int ROWS = cell_lengths->shape()[0];
   const int COLS = cell_lengths->shape()[1];
   printf("cell_lengths has shape %dx%d\n", ROWS, COLS);

   // Print the table of string lengths
   for (index i = 0; i < ROWS; i++)
   {
      for (index j = 0; j < COLS; j++)
      {
         printf("%d\t", (*cell_lengths)[i][j]);
      }
      printf("\n");
   }

   // Cleanup
   delete cell_lengths;

   return 0;
}
