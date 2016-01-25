CXX=g++
CFLAGS=-std=c++11 -Wall -c

OBJECT=$(CXX) $(CFLAGS) $^ -o $@

build: Graph.o main.o
	$(CXX) -std=c++11 -Wall $^ -o findNames

Graph.o: Graph.cpp
	$(OBJECT)

main.o: main.cpp
	$(OBJECT)