JUDGEFLAGS=-lm -lcrypt -O2 -pipe -DONLINE_JUDGE
CXXFLAGS=-g -Wall -pedantic

OBJECTS=team_queue submission

all: $(OBJECTS)

submission: team_queue.cpp
	$(CXX) $(JUDGEFLAGS) -o $@ $<
