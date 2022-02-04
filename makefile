# Include debug symbols and use c++17
CPP_FLAGS = -g -std=c++17

colopt: main.o parser.o
	g++ $(CPP_FLAGS) -o colopt main.o parser.o

main.o: main.cpp Matrix.h
	g++ $(CPP_FLAGS) -c main.cpp

parser.o: parser.h parser.cpp Matrix.h
	g++ $(CPP_FLAGS) -c parser.cpp

clean:
	rm colopt *.o
