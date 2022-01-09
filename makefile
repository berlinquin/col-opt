colopt: main.o parser.o
	g++ -o colopt main.o parser.o

main.o: main.cpp Matrix.h
	g++ -c main.cpp

parser.o: parser.h parser.cpp Matrix.h
	g++ -c parser.cpp

clean:
	rm colopt *.o
