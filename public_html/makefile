.PHONY: clean

# Look for dependencies in html_template/ directory
VPATH = html_template


index.html: hello3.cpp shell_minimal.html
	em++ -o index.html hello3.cpp -O0 \
		--shell-file html_template/shell_minimal.html \
		-I ../include \
		-s USE_BOOST_HEADERS=1 \
		-s NO_EXIT_RUNTIME \
		-s "EXPORTED_RUNTIME_METHODS=['ccall']" \
		-s "EXPORTED_FUNCTIONS=['_main','_malloc','_free']"

# PHONY targets
clean:
	rm index.html index.js index.wasm

