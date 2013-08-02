#define NDEBUG 
#include <climits>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <fstream>

#include "Heaps.h"

Heaps::Heaps(unsigned int sites, cost weight[], dist distance[]) {
    this->sites = sites;
    this->weight = weight;
    this->distance = distance;
}

void Heaps::calcFolds(unsigned int heaps) {
    fold = new cost*[sites];
    for(unsigned int initial=0; initial < sites; initial++) {
        unsigned int foldmax = std::min(sites-heaps+initial, sites-initial);
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
    // sites > 0
    // heaps > 0
    if(heaps == 1) {
        // 0 <= this->sites-sites < this->sites
        // 0 <= this->sites-sites+sites-1 = this->sites-1 < this->sites
        //return foldCost(this->sites-sites, sites-1);
        return fold[this->sites-sites][sites-1];
    }
    // heaps > 1
    cost minCost = COST_MAX;
    int newCost;
    //for(unsigned int folds=0; folds <= sites - heaps; folds++) {
    for(
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
        unsigned int maxhheaps = std::min(sites, heaps);
        solved[sites] = current;
        current += sites;
        // 1 <= sites <= this->sites
        // Subproblem (n,k) makes reference to (n-f-1,k-1)
        // So (first arg-second arg) <= (this->sites - heaps)
        for(unsigned int hheaps=1; hheaps <= maxhheaps; hheaps++) {
            // 1 <= hheaps <= sites
            // 1 <= hheaps <= heaps
            // 0 <= sites-hheaps <= sites-1
            solved[sites][sites-hheaps] = solveSubproblem(sites, hheaps);
        }
    }
    cost ret = solved[this->sites][this->sites-heaps];
    delete solved;
    delete costs;
    delete temp;
    return ret;
}
/*
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
*/
