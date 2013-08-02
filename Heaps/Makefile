all: run Heaps.class ProblemReader.class benchmark profile
CXX=g++
CXXFLAGS=-g -pg
LD=g++
LXX=g++

.PHONY: run clean

clean:
	rm *.o

benchmark: benchmark.o Dijkstra.o
	g++ -o $@ $^

profile: profile.o Heaps.o
	g++ -pg -o $@ $^

run: 

%.class: %.java
	javac -g $<
