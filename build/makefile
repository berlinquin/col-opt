# Compiler flags
# -g   include debug symbols
# -std use c++17 standard
# -I   add to the search path for #includes
CPP_FLAGS = -g -std=c++17 -I ../include/

.PHONY: clean

# Look for dependencies in src/ and include/ directories
VPATH = ../src:../include

# Original command-line program

# $@ is the name of the target (colopt in this case)
# $^ is the list of all prerequisites
colopt: main.o parser.o combination.o
	g++ $(CPP_FLAGS) -o $@ $^ -lClp -lCoinUtils && cp colopt ../

# $< is the first prerequisite (main.cpp in this case)
main.o: main.cpp parser.h table.h colopt.h approximate.h combination.h
	g++ $(CPP_FLAGS) -c $<

parser.o: parser.cpp rapidcsv/rapidcsv.h parser.h table.h
	g++ $(CPP_FLAGS) -c $<

combination.o: combination.cpp combination.h
	g++ $(CPP_FLAGS) -c $<

# Separate program to test generators
gentest: generator_test.o combination.o
	g++ $(CPP_FLAGS) -o gentest $^ && cp gentest ../

generator_test.o: generator_test.cpp combination.h
	g++ $(CPP_FLAGS) -c $<

# Separate programs to test linear programming library
clpdriver: clp/driver.cpp
	g++ $(CPP_FLAGS) -o $@ $^ -lClp

clpmod: clp/modify.cpp
	g++ $(CPP_FLAGS) -o $@ $^ -lClp -lCoinUtils

# PHONY targets
clean:
	rm colopt gentest clpdriver clpmod *.o

