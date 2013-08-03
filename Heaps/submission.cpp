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

#endif

#ifndef ONLINE_JUDGE
#define NDEBUG 
#include "Heaps.h"
#endif

#include <climits>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <cassert>

Heaps::Heaps(int sites, cost weight[], dist distance[]) {
    this->sites = sites;
    this->weight = weight;
    this->distance = distance;
}

void Heaps::calcFolds(int heaps) {
    fold = new cost*[sites];
    for(int initial=0; initial < sites; initial++) {
        int foldmax = std::min(sites-heaps+initial, sites-initial);
        // foldmax <= sites-heaps+initial
        // foldmax <= sites-initial
        fold[initial] = new cost[foldmax+1];
        cost acum = 0, barge = 0;
        fold[initial][0] = 0;
        for(int final = initial; final < initial+foldmax; final++) {
            // initial <= final < sites
            // final-initial+1 <= foldmax
            barge += weight[final];
            acum += barge * distance[final];
            fold[initial][final-initial+1] = acum;
        }
    }
}

cost Heaps::solveSubproblem(int sites, int heaps) {
    assert(sites >= 0);
    assert(heaps >= 0);
    assert(sites >= heaps);
    assert(sites <= this->sites);
    assert((heaps != 0)^(sites == 0));    // sites == 0 iff heaps == 0 
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
        return fold[this->sites-sites][sites-1];
    }
    // heaps > 1
    cost minCost = COST_MAX;
    int newCost;
    for(int folds=0; folds <= sites - heaps; folds++) {
    //cost* end = fold[this->sites-sites]+sites-heaps+1;
    //for(cost* foldcost = fold[this->sites-sites]; foldcost < end; foldcost++)
        // 0 <= folds <= sites-heaps
        // 0 <= this->sites-sites < this->sites
        // 0 <= this->sites-sites+folds <= this->sites-heaps <= this->sites
        // 0 <= sites-folds-1 <= sites - 1 <= this->sites - 1
        // 0 <= sites - heaps - folds <= this->sites
        // heaps-1 > 0
        newCost = fold[this->sites-sites][folds] + solved[sites-folds-1]
                                                         [sites-heaps-folds];
        minCost = newCost < minCost ? newCost : minCost;
    }
    return minCost;
}

cost Heaps::solve(int heaps) {
    calcFolds(heaps);
    temp = new cost[this->sites+1];
    solved = new cost*[this->sites + 1];
    cost *costs = new cost[1+sites*(sites+1)/2];
    cost *current = costs;
    solved[0] = current++;
    solved[0][0] = 0;
    for(int sites=1; sites <= this->sites; sites++) {
        int maxheaps = std::min(sites, heaps);
        int minheaps = std::max(1, heaps - this->sites + sites);
        solved[sites] = current;
        current += sites;
        // 1 <= sites <= this->sites
        // Subproblem (n,k) makes reference to (n-f-1,k-1)
        // So (first arg-second arg) <= (this->sites - heaps)
        for(int hh = minheaps; hh <= maxheaps; hh++) {
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
    for(int site=0; site < this->sites; site++) {
        delete [] fold[site];
    }
    delete [] fold;
    return ret;
}

#ifdef ONLINE_JUDGE

int main(int argc, char *argv[]) {
    while(true) {
        int sites, heaps;
        scanf("%d %d\n", &sites, &heaps);
        if(feof(stdin))
            break;
        cost *weight = new cost[sites];
        cost *distance = new cost[sites];
        int last_distance, this_distance;
        scanf("%d %d\n", &last_distance, &weight[0]);
        for(int i=1; i<sites; i++) {
            scanf("%d %d\n", &this_distance, &weight[i]);
            distance[i-1] = this_distance - last_distance;
            last_distance = this_distance;
        }
        printf("%d\n", Heaps(sites, weight, distance).solve(heaps));
        delete [] weight;
        delete [] distance;
    }
}

#endif  // ONLINE_JUDGE
