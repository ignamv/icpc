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
                cost bargeLoad;
                unsigned int heaps;
                State(unsigned int _site, cost _bargeLoad, unsigned int _heaps):
                    site(_site), bargeLoad(_bargeLoad), heaps(_heaps) {}
                bool operator< (const State y) const {
                    return site != y.site ? site < y.site
                         : bargeLoad != y.bargeLoad ? bargeLoad < y.bargeLoad
                         : heaps < y.heaps;
                }
        };
        class DistState {
            public:
                State s;
                dist d;
                bool operator< (DistState y) {
                    return d< y.d;
                }
        };
        State load(State);
        bool canLoad(State);
        bool canUnload(State);
        cost loadCost(State);
        State unload(State);
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

