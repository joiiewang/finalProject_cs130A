CXX = g++
CXXFLAGS = -g -std=c++11

main: main.o friendshipGraph.o
	${CXX} $^ -o main

clean:
	/bin/rm -f main *.o