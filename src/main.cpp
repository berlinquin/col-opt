#include <iostream>
#include <filesystem>

#include "parser.h"
#include "table.h"
#include "colopt.h"
#include "approximate.h"
#include "global.h"



void printUsage()
{
   printf("Usage: colopt [-v] -w <width> <filename>\n"
          "  e.g. colopt -w 80 data.csv\n");
}

int main(int argc, char *argv[])
{
   // Alias the std::filesystem namespace
   namespace fs = std::filesystem;

   // Make sure that three args were passed,
   // and that the first arg is the -w flag
   if (argc < 4)
   {
      printf("Error: %d arguments passed, 3 expected\n", (argc-1));
      printUsage();
      return 1;
   }

   // print extra content to stdout
   colopt::verbose = false;
   // index to the width string in argv
   int width_i = 0;

   // Parse CLI args
   for (int i = 1; i < argc; i++)
   {
      if (argv[i] == std::string("-v"))
      {
         colopt::verbose = true;
      }
      else if (argv[i] == std::string("-w"))
      {
         width_i = i+1;
      }
   }
   if (width_i == 0 || width_i >= argc)
   {
      printf("Error: missing or invalid width flag");
      printUsage();
      return 1;
   }

   // Parse the width and filename from the given args
   int width;
   std::string filename = argv[argc-1];
   try
   {
      // can throw std::invalid_argument or std::out_of_range
      width = std::stoi(argv[width_i]);
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
   string_table_type *cell_text;
   table_type *cell_lengths;
   // TODO parse file into 2D array of strings
   bool success = parse_csv(filename, &cell_text, &cell_lengths);
   if (!success)
   {
      return 1;
   }

   // table_type has two dimensions by definition
   const int ROWS = cell_lengths->shape()[0];
   const int COLS = cell_lengths->shape()[1];
   if (colopt::verbose)
   {
      printf("Table has shape %dx%d\n", ROWS, COLS);
   }

   // Do a naive optimization of the table.
   // This takes a long time to run!
   //optimize<>(*cell_lengths, width);

   // Approximate the best widths with linear programming
   std::vector<int> widths = approximate<>(*cell_lengths, width);
   if (colopt::verbose)
   {
      printf("approximate best widths: [");
      for (int i = 0; i < widths.size(); ++i)
      {
         printf("%d, ", widths[i]);
      }
      printf("]\n");
   }

   // Print the table of string lengths
   /*
   for (table_index i = 0; i < ROWS; i++)
   {
      for (table_index j = 0; j < COLS; j++)
      {
         printf("%d\t", (*cell_lengths)[i][j]);
      }
      printf("\n");
   }
   */

   // Print out the optimized table to stdout
   for (int i = 0; i < ROWS; i++)
   {
      // Calculate the number of lines this row will take
      int row_len = 0;
      for (int j = 0; j < COLS; j++)
      {
         int cell_rows = std::ceil(1.0 * (*cell_lengths)[i][j] / widths[j]);
         row_len = std::max(row_len, cell_rows);
      }
      for (int k = 0; k < row_len; k++)
      {
         // For each cell in the row,
         // print characters in range [k, k+widths[j])
         for (int j = 0; j < COLS; j++)
         {
            int start = k*widths[j];
            int next_window_start = (k+1)*widths[j];
            int string_len = (*cell_lengths)[i][j];
            int upper_bound = std::min(next_window_start, string_len);
            if (start < upper_bound)
            {
               // print to std out, padded to width characters
               const char *c = (*cell_text)[i][j].c_str();
               int size = upper_bound - start;
               std::string_view sv(c + start, size);
               // Left align the string, filled to space widths[j]
               std::cout << std::left << std::setw(widths[j]) << sv;
            }
            else
            {
               // print spaces only (an empty column)
               std::cout << std::setw(widths[j]) << "";
            }
            // Don't print divider bar after last column
            if (j < COLS-1)
            {
               std::cout << "|";
            }
         }
         std::cout << std::endl;
      }
   }

   // Cleanup
   delete cell_lengths;
   delete cell_text;

   return 0;
}
