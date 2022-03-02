# Compiler flags
# -g   include debug symbols
# -std use c++17 standard
# -I   add to the search path for #includes
CPP_FLAGS = -g -std=c++17 -I include/

.PHONY: clean time

# Look for dependencies in src/ and include/ directories
VPATH = src:include

# Original command-line program

# $@ is the name of the target (colopt in this case)
# $^ is the list of all prerequisites
colopt: main.o parser.o colopt.o combination.o
	g++ $(CPP_FLAGS) -o $@ $^

# $< is the first prerequisite (main.cpp in this case)
main.o: main.cpp parser.h table.h colopt.h combination.h
	g++ $(CPP_FLAGS) -c $<

parser.o: parser.cpp rapidcsv/rapidcsv.h parser.h table.h
	g++ $(CPP_FLAGS) -c $<

colopt.o: colopt.cpp colopt.h table.h combination.h
	g++ $(CPP_FLAGS) -c $<

combination.o: combination.cpp combination.h
	g++ $(CPP_FLAGS) -c $<

# Separate program to test generators
gentest: generator_test.o combination.o
	g++ $(CPP_FLAGS) -o gentest $^

generator_test.o: generator_test.cpp combination.h
	g++ $(CPP_FLAGS) -c $<

# PHONY targets
clean:
	rm colopt gentest *.o

time: colopt
	/usr/bin/bash -c 'time ./colopt -w 20 ramen-ratings.csv > /dev/null'

