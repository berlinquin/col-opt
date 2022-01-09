#include <vector>

#include "rapidcsv/rapidcsv.h"
#include "parser.h"

bool parse_csv(const char *filename, array_type **out)
{
   rapidcsv::Document csv_file(filename);
   const int ROWS = csv_file.GetRowCount();
   const int COLS = csv_file.GetColumnCount();
   // Create a 2D array with the same dimensions as the csv file
   *out = new array_type(boost::extents[ROWS][COLS]);
   // Iterate over the csv, for each cell
   for (size_t i = 0; i < ROWS; i++)
   {
      std::vector<std::string> row = csv_file.GetRow<std::string>(i);
      printf("%d\n", i);
      for (int j = 0; j < COLS; j++)
      {
         printf("%d %s\n", j, row[j].c_str());
         (**out)[i][j] = row[j].size();
      }
   }
   return true;
}

