#include <vector>

#include "rapidcsv/rapidcsv.h"
#include "Matrix.h"

bool parse_csv(const char *filename, Matrix **out)
{
   rapidcsv::Document csv_file(filename);
   const int ROWS = csv_file.GetRowCount();
   for (size_t i = 0; i < ROWS; i++)
   {
      std::vector<int> row = csv_file.GetRow<int>(i);
   }
   return true;
}

