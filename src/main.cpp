#include <iostream>
#include <filesystem>

#include "parser.h"
#include "table.h"
#include "colopt.h"



void printUsage()
{
   printf("Usage: colopt -w <width> <filename>\n"
          "  e.g. colopt -w 80 data.csv\n");
}

int main(int argc, char *argv[])
{
   // Alias the std::filesystem namespace
   namespace fs = std::filesystem;

   // Make sure that three args were passed,
   // and that the first arg is the -w flag
   if (argc != 4)
   {
      printf("Error: %d arguments passed, 3 expected\n", (argc-1));
      printUsage();
      return 1;
   }
   else if (argv[1] != std::string("-w"))
   {
      printf("Error: flag '%s' not recognized\n", argv[1]);
      printUsage();
      return 1;
   }

   // Parse the width and filename from the given args
   int width;
   std::string filename = argv[3];
   try
   {
      // can throw std::invalid_argument or std::out_of_range
      width = std::stoi(argv[2]);
      // can throw implementation defined exceptions
      fs::path path { filename };
      // can throw fs::filesystem_error
      if (!fs::exists(path))
      {
         printf("Error: file '%s' does not exist\n", argv[3]);
         return 1;
      }
   }
   catch (const std::invalid_argument& e)
   {
      printf("Error: could not parse int from string '%s'\n", argv[2]);
      return 1;
   }
   catch (...)
   {
      printf("Error: could not parse arguments\n");
      return 1;
   }

   // Parse the input file into a table of cell lengths
   table_type *cell_lengths;
   bool success = parse_csv(filename, &cell_lengths);
   if (!success)
   {
      return 1;
   }

   // table_type has two dimensions by definition
   const int ROWS = cell_lengths->shape()[0];
   const int COLS = cell_lengths->shape()[1];
   printf("cell_lengths has shape %dx%d\n", ROWS, COLS);

   // TODO implement the naive approach
   // - write a cost function
   // - take an integer (total width) as input from the user
   // - iterate over all possible column splits, run the cost function
   // - print out the optimal column widths

   // Do a naive optimization of the table
   optimize(*cell_lengths, width);

   // Print the table of string lengths
   for (table_index i = 0; i < ROWS; i++)
   {
      for (table_index j = 0; j < COLS; j++)
      {
         printf("%d\t", (*cell_lengths)[i][j]);
      }
      printf("\n");
   }

   // Cleanup
   delete cell_lengths;

   return 0;
}
