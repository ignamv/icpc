

class Heaps {
    // Distance from this site to the next
    int[] distance;
    // Weight of this site's heap
    int[] weight;
    // Number of sites
    int sites;
    // foldCost[i][j] = Cost of folding j heaps starting from site i
    // *fold 0 heaps = do nothing
    // *fold 1 heap  = take heap i to i+1
    // *fold 2 heaps = take heap i to i+1 and then take i+1 to i+2
    // *and so on
    int[][] foldCost;

    public Heaps(int[] _distance, int[] _weight) {
        distance = _distance;
        weight = _weight;
        sites = weight.length;
    }

    int[][] calcFoldCost(int nheaps) {
        // Calculate all necessary fold costs for assembling nheaps heaps
        int[][] cost = new int[sites-1][];
        for(int ii=0; ii<sites-1; ii++) {
            // *Can't fold past the last site
            // *Will never fold so many sites that I can't get the required 
            // number of heaps
            int maxfold = Math.min(sites-ii-1, sites-nheaps);
            cost[ii] = new int[maxfold+1];
            cost[ii][0] = 0;
            int barge_load = weight[ii];
            for(int jj=1; jj<cost[ii].length; jj++) {
                cost[ii][jj] = cost[ii][jj-1] + barge_load * distance[ii+jj-1];
                barge_load += weight[ii+jj];
            }
        }
        return cost;
    }

    public int solve(int nheaps) {
        int[][] foldCost = calcFoldCost(nheaps);
        // Cost of sub-problems
        // First index: number of sites to visit. From 1 to sites.
        // Second index: number of heaps to assemble. From 1 to the first
        // index.
        // 1-based indexing for prettier code
        int[][] subproblem;
        subproblem = new int[sites+1][];
        subproblem[0] = new int[] {0};
        // Solve the subproblem for 1..sites sites left to visit
        for(int sites_left=1; sites_left<=sites; sites_left++) {
            int max_heaps = Math.min(nheaps, sites_left);
            int current_site = sites-sites_left;
            subproblem[sites_left] = new int[max_heaps + 1];
            // No need to carry loads if I already have the required number
            // of heaps
            if(max_heaps == sites_left) {
                subproblem[sites_left][sites_left] = 0;
                max_heaps--;
            }
            // Solve the subproblem for each possible number of heaps desired
            // I can't assemble less than 1 heap
            // I also don't need to assemble less than nheaps-current_site
            // heaps
            for(int heaps = Math.max(1,nheaps-current_site); 
                    heaps <= max_heaps; heaps++) {
                // Select the minimum cost out of folding "loads" sites
                // for 0 <= loads <= sites_left-heaps
                //
                // The cost of each option is the cost of this fold
                // operation plus the cost of assembling the remaining heaps
                // (which is a subproblem I've already solved)
                if(heaps == 1) {
                    // Gotta take all the heaps to the last site
                    subproblem[sites_left][heaps] = foldCost[current_site]
                                                            [sites_left-1];
                    continue;
                }
                int mincost = Integer.MAX_VALUE;
                for(int loads=0; loads <= sites_left - heaps; loads++) {
                    int newcost = foldCost[current_site][loads]
                                + subproblem[sites_left-loads-1][heaps-1];
                    mincost = Math.min(mincost, newcost);
                }
                subproblem[sites_left][heaps] = mincost;
            }
        }
        return subproblem[sites][nheaps];
    }
}

