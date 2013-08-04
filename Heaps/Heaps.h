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

        void calcFolds(int heaps);
        cost solveSubproblem(int sites, int heaps);
    public:
        Heaps(int sites, cost weight[], dist distance[]);
        
        cost solve(int heaps);
};

#endif // HEAPS_H

