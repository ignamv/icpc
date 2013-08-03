#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include "Heaps.h"

int randint(int max) {
    return random() % max;
}

int main(int argc, char *argv[]) {

    const int sites = 1000;
    cost weight[sites];
    int distance[sites];
    for(int site = 0; site<sites; site++) {
        weight[site] = randint(20);
        distance[site] = randint(20);
    }
    timespec start, end;
    if(clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start) != 0) {
        perror("Timing start");
    }
    Heaps(sites, weight, distance).solve(400);
    if(clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end) != 0) {
        perror("Timing end");
    }
    printf("%e\n",end.tv_sec-start.tv_sec+1e-9*(end.tv_nsec-start.tv_nsec));
}
