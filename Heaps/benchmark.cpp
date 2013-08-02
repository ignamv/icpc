#include <cstdio>
#include <stdlib.h>
#include <time.h>
//#include "Heaps.h"
#include "Dijkstra.h"

int randint(int max) {
    return random() % max;
}

int main(int argc, char *argv[]) {
    srandom(time(NULL));
    int sites = 1000;
    int minheaps = 10;
    int heapstep = 50;
    int rounds = 20;
    int maxdist = 10;
    int maxweight = 30;
    int repeats = 10;
    double round[repeats];
    double mean[rounds];
    double std[rounds];
    cost weight[sites];
    unsigned int distance[sites];
    int nround = 0;
    printf("Heaps\tMean\tStd\n");
    for(int nround=0; nround<rounds; nround++) {
        int heaps = minheaps + heapstep*nround;
        for(int repeat=0; repeat<repeats; repeat++) {
            for(int site = 0; site<sites; site++) {
                weight[site] = randint(maxweight);
                distance[site] = randint(maxdist);
            }
            timespec start, end;
            if(clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start) != 0) {
                perror("Timing start");
            }
            Heaps(sites, weight, distance).solve(heaps);
            if(clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end) != 0) {
                perror("Timing end");
            }
            round[repeat] = end.tv_sec-start.tv_sec+1e-9*(end.tv_nsec-start.tv_nsec);
            mean[nround] += round[repeat];
            std[nround] += round[repeat]*round[repeat];
        }
        mean[nround] /= repeats;
        std[nround] = (std[nround]-mean[nround]*mean[nround])/(repeats-1);
        printf("%d\t%e\t%e\n", heaps, mean[nround], std[nround]);
    }
    return 0;
}


