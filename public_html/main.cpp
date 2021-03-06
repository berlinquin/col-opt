// Copied from Mozilla tutorial: https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm
#include <cstdio>
#include <algorithm>
#include <emscripten/emscripten.h>
#include "table.h"
#include "colopt.h"

using std::printf;

int main() {
    printf("Hello World\n");
}

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE int* process_table(uint16_t *table, int rowsParsed, int columns)
{
	printf("process_table() called with args:\n"
			"table: %p, rowsParsed: %d, columns: %d\n",
			table, rowsParsed, columns);
	// Print as boost multiarray
	printf("Boost multiarray:\n");
	table_type_ref boost_table(table, boost::extents[rowsParsed][columns]);
	for (table_index i  = 0; i < rowsParsed; i++)
	{
		printf("row %ld: [", i);
		for (table_index j = 0; j < columns; j++)
		{
			uint16_t x = boost_table[i][j];
			printf("%hd, ", x);
		}
		printf("]\n");
	}
	// Call to optimize
	std::vector<int> optimal_widths = optimize<>(boost_table, 20);
	// Copy to widths array to heap and return pointer
	int *buffer = (int*)calloc(optimal_widths.size(), sizeof(int));
	std::copy<>(optimal_widths.begin(), optimal_widths.end(), buffer);
	return buffer;
}

#ifdef __cplusplus
}
#endif

