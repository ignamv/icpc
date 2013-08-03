#ifndef HEAPS_H

#define HEAPS_H

#include <climits>

typedef unsigned int cost;
typedef unsigned int dist;

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
        unsigned int sites;

        void calcFolds(unsigned int heaps);
        inline cost foldCost(unsigned int initial, unsigned int length);
        inline cost solveSubproblem(unsigned int sites, unsigned int heaps);
    public:
        Heaps(unsigned int sites, cost weight[], dist distance[]);
        
        cost solve(unsigned int heaps);
};

#endif

#define NDEBUG 
#include <climits>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <fstream>

#ifndef ONLINE_JUDGE
#include "Heaps.h"
#endif

Heaps::Heaps(unsigned int sites, cost weight[], dist distance[]) {
    this->sites = sites;
    this->weight = weight;
    this->distance = distance;
}

void Heaps::calcFolds(unsigned int heaps) {
    fold = new cost*[sites];
    for(unsigned int initial=0; initial < sites; initial++) {
        unsigned int foldmax = std::min((int)(sites-heaps+initial),
                                        (int)(sites-initial))+1;
        // foldmax <= sites-heaps+initial
        // foldmax <= sites-initial
        fold[initial] = new cost[foldmax+1];
        cost acum = 0, barge = 0;
        fold[initial][0] = 0;
        for(unsigned int final = initial; final < initial+foldmax; final++) {
            // initial <= final < sites
            // final-initial+1 <= foldmax
            barge += weight[final];
            acum += barge * distance[final];
            fold[initial][final-initial+1] = acum;
        }
    }
}

inline cost Heaps::foldCost(unsigned int initial, unsigned int length) {
    assert(initial+length < sites);
    return fold[initial][length];
}


inline cost Heaps::solveSubproblem(unsigned int sites, unsigned int heaps) {
    assert(sites >= heaps);
    assert(sites <= this->sites);
    assert(heaps != 0 ^ sites == 0);    // sites == 0 iff heaps == 0 
    // Have to fold a total of (sites-heaps) times
    if(sites == heaps) {
        // Skip the remaining sites
        // This is a shortcut. The condition is also handled by 
        // successive a 0-length folds
        return 0;
    }
    assert(sites > 0);
    assert(heaps > 0);
    if(heaps == 1) {
        assert(0 <= this->sites-sites && this->sites-sites < this->sites);
        assert(0 <= this->sites-1 && this->sites-1 < this->sites);
        //return foldCost(this->sites-sites, sites-1);
        /*printf("initial %d length %d\n",this->sites-sites,sites-1);
        fflush(stdout);*/
        return fold[this->sites-sites][sites-1];
    }
    // heaps > 1
    cost minCost = COST_MAX;
    unsigned int newCost;
    for(unsigned int folds=0; folds <= sites - heaps; folds++) {
    //cost* end = fold[this->sites-sites]+sites-heaps+1;
    //for(cost* foldcost = fold[this->sites-sites]; foldcost < end; foldcost++)
        // 0 <= folds <= sites-heaps
        // 0 <= this->sites-sites < this->sites
        // 0 <= this->sites-sites+folds <= this->sites-heaps <= this->sites
        // 0 <= sites-folds-1 <= sites - 1 <= this->sites - 1
        // 0 <= sites - heaps - folds <= this->sites
        // heaps-1 > 0
        //minCost = std::min(minCost, foldCost(this->sites-sites, folds)
        newCost = fold[this->sites-sites][folds] + solved[sites-folds-1]
                                                         [sites-heaps-folds];
        minCost = newCost < minCost ? newCost : minCost;
    }
    return minCost;
}

cost Heaps::solve(unsigned int heaps) {
    calcFolds(heaps);
    temp = new cost[this->sites+1];
    solved = new cost*[this->sites + 1];
    cost *costs = new cost[1+sites*(sites+1)/2];
    cost *current = costs;
    solved[0] = current++;
    solved[0][0] = 0;
    for(unsigned int sites=1; sites <= this->sites; sites++) {
        unsigned int maxheaps = std::min(sites, heaps);
        unsigned int minheaps = std::max(1, (int)(heaps - this->sites + sites));
        solved[sites] = current;
        current += sites;
        // 1 <= sites <= this->sites
        // Subproblem (n,k) makes reference to (n-f-1,k-1)
        // So (first arg-second arg) <= (this->sites - heaps)
        for(unsigned int hh = minheaps; hh <= maxheaps; hh++) {
            // 1 <= hh <= sites
            // 1 <= hh <= heaps
            // 0 <= sites-hh <= sites-1
            solved[sites][sites-hh] = solveSubproblem(sites, hh);
        }
    }
    cost ret = solved[this->sites][this->sites-heaps];
    delete [] solved;
    delete [] costs;
    delete [] temp;
    for(unsigned int site=0; site < this->sites; site++) {
        delete [] fold[site];
    }
    delete [] fold;
    return ret;
}

#ifdef ONLINE_JUDGE

int main(int argc, char *argv[]) {

    while(true) {
        unsigned int sites, heaps;
        scanf("%d %d\n", &sites, &heaps);
        if(feof(stdin))
            break;
        cost *weight = new cost[sites];
        cost *distance = new cost[sites-1];
        int last_distance, this_distance;
        scanf("%d %d\n", &last_distance, &weight[0]);
        for(unsigned int i=1; i<sites; i++) {
            scanf("%d %d\n", &this_distance, &weight[i]);
            distance[i-1] = this_distance - last_distance;
            last_distance = this_distance;
        }
        printf("%d\n", Heaps(sites, weight, distance).solve(heaps));
        delete weight;
        delete distance;
    }
}

#endif  // ONLINE_JUDGE
