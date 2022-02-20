# Include debug symbols and use c++17
CPP_FLAGS = -g -std=c++17

.PHONY: clean time

colopt: main.o parser.o colopt.o combination.o
	g++ $(CPP_FLAGS) -o colopt main.o parser.o colopt.o combination.o

main.o: main.cpp table.h combination.h
	g++ $(CPP_FLAGS) -c main.cpp

parser.o: parser.h parser.cpp table.h
	g++ $(CPP_FLAGS) -c parser.cpp

colopt.o: colopt.h colopt.cpp table.h combination.h
	g++ $(CPP_FLAGS) -c colopt.cpp

combination.o: combination.h combination.cpp
	g++ $(CPP_FLAGS) -c combination.cpp

clean:
	rm colopt *.o

time: colopt
	/usr/bin/bash -c 'time ./colopt -w 20 ramen-ratings.csv > /dev/null'

