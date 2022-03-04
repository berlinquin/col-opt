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
	for (int i = 0; i < rowsParsed; i++)
	{
		printf("row %d: [", i);
		for (int j = 0; j < columns; j++)
		{
			int index = i*columns + j;
			uint16_t x = table[index];
			printf("%hd, ", x);
		}
		printf("]\n");
	}
	// Print individual bytes
	/*
	printf("print individual bytes\n");
	int bytes = rowsParsed * columns * 2;
	uint8_t *table_bytes = (uint8_t*) table;
	for (int i = 0; i < bytes; i++)
	{
		printf("%p: %x\n", (table_bytes+i), table_bytes[i]);
		if (i > 0 && i % (columns*2) == (columns*2)-1)
		{
			printf("\n");
		}
	}
	printf("\n");
	*/
}

#ifdef __cplusplus
}
#endif

