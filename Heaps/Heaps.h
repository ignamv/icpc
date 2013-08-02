#ifndef HEAPS_H

#define HEAPS_H

#include <climits>

typedef int cost;
typedef int dist;

class Heaps {
    private:
        static const cost COST_MAX = INT_MAX;

        cost *weight;
        // solved[i,j] is cost of problem with i remaining sites
        // and i-j remaining heaps
        cost **solved;
        // Pre-compute cost of folding j times from site i
        cost **fold;
        dist *distance;
        cost *temp;
        int sites;

        void calcFolds(unsigned int heaps);
        inline cost foldCost(unsigned int initial, unsigned int length);
        inline cost solveSubproblem(unsigned int sites, unsigned int heaps);
    public:
        Heaps(unsigned int sites, cost weight[], dist distance[]);
        
        cost solve(unsigned int heaps);
};

#endif

