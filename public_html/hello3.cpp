// Copied from Mozilla tutorial: https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm
#include <stdio.h>
#include <emscripten/emscripten.h>
//#include "../include/table.h"

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
	// Print as 2D array
	int i = 0;
	int j = 0;
	for (i = 0; i < rowsParsed; i++)
	{
		printf("row %d: [", i);
		for (j = 0; j < columns; j++)
		{
			int index = i*columns + j;
			printf("%hd, ", table[index]);
		}
		printf("]\n");
	}
	printf("last address: %p\n", &(table[i*columns + j]));
	// Print as flat array
	uint16_t *table_flat = reinterpret_cast<uint16_t*>(table);
	int length = rowsParsed * columns;
	printf("[");
	for (i = 0; i < length; i++)
	{
		printf("%hd, ", table_flat[i]);
	}
	printf("]\n");
	printf("last address: %p\n", &(table_flat[i]));
}

#ifdef __cplusplus
}
#endif

