.PHONY: clean

# Look for dependencies in html_template/ directory
VPATH = ../src:../include:html_template


index.html: hello3.cpp table.h colopt.h shell_minimal.html combination.o
	em++ -o index.html hello3.cpp combination.o -O0 \
		--shell-file html_template/shell_minimal.html \
		-I ../include \
		-s USE_BOOST_HEADERS=1 \
		-s NO_EXIT_RUNTIME \
		-s "EXPORTED_RUNTIME_METHODS=['ccall']" \
		-s "EXPORTED_FUNCTIONS=['_main','_malloc','_free']"

combination.o: combination.cpp combination.h
	em++ -c $< -O0 \
		-I ../include

# PHONY targets
clean:
	rm index.html index.js index.wasm combination.o

