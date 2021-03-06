#include <vector>

#include "rapidcsv/rapidcsv.h"
#include "parser.h"

bool parse_csv(const std::string& filename, string_table_type **text, table_type **lengths)
{
   // Treat all columns and rows as data (i.e. no header row)
   rapidcsv::LabelParams lp {-1, -1};
   // Create a document with the given filename and params
   rapidcsv::Document csv_file(filename, lp);
   const int ROWS = csv_file.GetRowCount();
   const int COLS = csv_file.GetColumnCount();
   // Create a 2D array with the same dimensions as the csv file
   *text = new string_table_type(boost::extents[ROWS][COLS]);
   *lengths = new table_type(boost::extents[ROWS][COLS]);
   // Iterate over the csv, for each cell
   for (int i = 0; i < ROWS; i++)
   {
      std::vector<std::string> row = csv_file.GetRow<std::string>(i);
      // Force all rows to have the same number of columns
      if (row.size() != COLS)
      {
         printf("Error: row %d has %d columns, %d columns expected.\n", i, row.size(), COLS);
         return false;
      }
      // Print the row number
      //printf("%d\n", i);
      for (int j = 0; j < COLS; j++)
      {
         // Print the column number and cell contents
         //printf("%d %s\n", j, row[j].c_str());
         // Write the string to output matrix
         (**text)[i][j] = row[j];
         // Write the string's length to output matrix
         (**lengths)[i][j] = row[j].size();
      }
   }
   return true;
}

