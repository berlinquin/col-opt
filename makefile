# Include debug symbols and use c++17
CPP_FLAGS = -g -std=c++17

.PHONY: clean time

# Original command-line program
colopt: main.o parser.o colopt.o combination.o
	g++ $(CPP_FLAGS) -o colopt main.o parser.o colopt.o combination.o

main.o: main.cpp parser.h table.h colopt.h combination.h
	g++ $(CPP_FLAGS) -c main.cpp

parser.o: parser.cpp rapidcsv/rapidcsv.h parser.h table.h
	g++ $(CPP_FLAGS) -c parser.cpp

colopt.o: colopt.cpp colopt.h table.h combination.h
	g++ $(CPP_FLAGS) -c colopt.cpp

combination.o: combination.cpp combination.h
	g++ $(CPP_FLAGS) -c combination.cpp

# Separate program to test generators
gentest: generator_test.o combination.o
	g++ $(CPP_FLAGS) -o gentest generator_test.o combination.o

generator_test.o: generator_test.cpp combination.h
	g++ $(CPP_FLAGS) -c generator_test.cpp

# PHONY targets
clean:
	rm colopt gentest *.o

time: colopt
	/usr/bin/bash -c 'time ./colopt -w 20 ramen-ratings.csv > /dev/null'

