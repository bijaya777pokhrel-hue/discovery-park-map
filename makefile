all: ShortestPath

ShortestPath: main.o AdjMatrix.o miniVector.o
	g++ -fsanitize=address -g -o ShortestPath main.o AdjMatrix.o miniVector.o

main.o: main.cpp
	g++ -c main.cpp

AdjMatrix.o: AdjMatrix.h AdjMatrix.cpp
	g++ -c AdjMatrix.h AdjMatrix.cpp

miniVector.o: miniVector.h miniVector.cpp
	g++ -c miniVector.h miniVector.cpp

clean:
	rm *.o ShortestPath
