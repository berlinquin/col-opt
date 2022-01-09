colopt: main.o parser.o
	g++ -g -o colopt main.o parser.o

main.o: main.cpp Matrix.h
	g++ -c -g main.cpp

parser.o: parser.h parser.cpp Matrix.h
	g++ -c -g parser.cpp

clean:
	rm colopt *.o
