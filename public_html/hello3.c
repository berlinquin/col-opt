// Copied from Mozilla tutorial: https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm
#include <stdio.h>
#include <emscripten/emscripten.h>

int main() {
    printf("Hello World\n");
}

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char ** argv) {
    printf("MyFunction Called\n");
}

EMSCRIPTEN_KEEPALIVE void process_table(uint16_t **table, int rowsParsed, int columns)
{
	printf("process_table() called with args:\n"
			"table: %p, rowsParsed: %d, columns: %d\n",
			table, rowsParsed, columns);
}

#ifdef __cplusplus
}
#endif

