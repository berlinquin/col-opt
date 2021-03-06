#include "table.h"

// Parse the csv given by filename
// and update the Matrix pointer to a Matrix
// holding the length of the text in each cell of the csv file
bool parse_csv(const std::string& filename, string_table_type **text, table_type **lengths);

