CXX=g++
CC=g++
CXXFLAGS=-g -pg -Wall -pedantic -Werror
LD=g++
LXX=g++
OBJECTS=Heaps.class ProblemReader.class profile submission Heaps.o submission.cpp 

all: $(OBJECTS)

.PHONY: run clean

clean:
	rm -f $(OBJECTS)

submission: submission.cpp
	$(CXX) $(CXXFLAGS) -lm -lcrypt -O2 -pipe -DONLINE_JUDGE -o $@ $^

submission.cpp: Heaps.cpp Heaps.h
	cat Heaps.h Heaps.cpp > submission.cpp

Heaps.o: Heaps.cpp Heaps.h

benchmark: benchmark.o Dijkstra.o
	g++ -o $@ $^

profile: profile.o Heaps.o
	g++ -pg -o $@ $^

%.class: %.java
	javac -g $<
