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
   Matrix *cell_lengths;
   bool success = parse_csv(argv[1], &cell_lengths);
   return 0;
}
