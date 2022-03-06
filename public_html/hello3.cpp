// Copied from Mozilla tutorial: https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm
#include <stdio.h>
#include <emscripten/emscripten.h>
#include "table.h"
#include "colopt.h"

int main() {
    printf("Hello World\n");
}

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char ** argv) {
    printf("MyFunction Called\n");
}

EMSCRIPTEN_KEEPALIVE void process_table(uint16_t *table, int rowsParsed, int columns)
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
	optimize(boost_table, 20);
}

#ifdef __cplusplus
}
#endif

