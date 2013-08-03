#include "Dijkstra.h"

Heaps::Heaps(unsigned int _sites, cost *_weight, unsigned int *_distance):
    sites(_sites),
    weight(_weight),
    distance(_distance) {
}

cost Heaps::solve(unsigned int heaps) {
    unvisited.insert(costState(0,State(0, 0, heaps)));
    while(true) {
        costState pair = *unvisited.begin();
        State current = pair.second;
        unvisited.erase(unvisited.begin());
        if(visited.find(current) != visited.end())
            continue;
        cost c = pair.first;
        if(current.site == sites-1)
            return c;
        if(current.
        if(canLoad(current)) {
            State sload = load(current);
            if(visited.find(sload) == visited.end())
                unvisited.insert(costState(c+loadCost(sload), sload));
        }
        if(canUnload(current)) {
            State sunload = unload(current);
            if(visited.find(sunload) == visited.end())
                unvisited.insert(costState(c, sunload));
        }

    }
    return 3;
}

/*
int main(int argc, char *argv[]) {

    while(true) {
        unsigned int sites, heaps;
        scanf("%d %d\n", &sites, &heaps);
        if(feof(stdin))
            break;
        cost *weight = new cost[sites];
        unsigned int *distance = new unsigned int[sites-1];
        unsigned int last_distance, this_distance;
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
