#include <vector>
#include "table.h"

// Return the cost of the table
// as its length in lines for the given widths
int cost(const table_type& table, const std::vector<int>& widths);

// Optimize the table to fit in the given width,
// printing out optimal width and total lines to stdout
void optimize(const table_type& table, int width);

