#include <cstdio>
#include <set>
#include <map>

typedef unsigned int cost;
typedef unsigned int dist;

class Heaps {
    private:
        class State {
            public:
                unsigned int site;
                unsigned int heaps;
                State(unsigned int _site,  unsigned int _heaps):
                    site(_site), heaps(_heaps) {}
                bool operator< (const State y) const {
                    return site != y.site ? site < y.site
                         : heaps < y.heaps;
                }
        };
        class DistState {
            public:
                State s;
                dist d;
                bool operator< (DistState y) {
                    return d < y.d;
                }
        };
        cost *weight;
        dist *distance;
        int sites;
        std::multimap<cost,State> unvisited;
        typedef std::pair<cost,State> costState;
        std::set<State> visited;
    public:
        Heaps(unsigned int sites, cost *weight, unsigned int *distance);
        cost solve(unsigned int heaps);
};

