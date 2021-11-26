colopt: main.o parser.o Matrix.o
	g++ -o colopt main.o Matrix.o parser.o

main.o: main.cpp
	g++ -c main.cpp

parser.o: parser.h parser.cpp
	g++ -c parser.cpp

Matrix.o: Matrix.h Matrix.cpp
	g++ -c Matrix.cpp

clean:
	rm colopt *.o
