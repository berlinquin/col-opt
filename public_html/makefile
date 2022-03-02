.PHONY: clean

# Look for dependencies in html_template/ directory
VPATH = html_template


index.html: hello3.c shell_minimal.html
	emcc -o index.html hello3.c -O3 \
		--shell-file html_template/shell_minimal.html \
		-s NO_EXIT_RUNTIME \
		-s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"

# PHONY targets
clean:
	rm index.html index.js index.wasm

