JUDGEFLAGS=-lm -lcrypt -O2 -pipe -DONLINE_JUDGE
CXXFLAGS=-g -Wall -pedantic

OBJECTS=chain_mult submission

all: $(OBJECTS)

submission: chain_mult.cpp
	$(CXX) $(JUDGEFLAGS) -o $@ $<
