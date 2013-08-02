
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.io.BufferedInputStream;

class Main {
    static class Heaps {
        // Distance from each site to the next
        int[] distance;
        // Weight of each site's heap
        int[] weight;
        // Number of sites
        int sites;
        // foldCost[i][j] = Cost of folding j heaps starting from site i
        // *fold 0 heaps = do nothing
        // *fold 1 heap  = take heap i to i+1
        // *fold 2 heaps = take heap i to i+1 and then take i+1 to i+2
        // *and so on
        int[][] foldCost;
        // Cost of sub-problems
        // First index: number of sites to visit. From 1 to sites.
        // Second index: number of heaps to assemble. From 1 to the first
        // index.
        // 1-based indexing for prettier code
        int[][] subproblem;

        public Heaps(int[] distance, int[] weight) {
            this.distance = distance;
            this.weight = weight;
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

        private int solveSubproblem(int sites_left, int heaps) {
            // Minimum cost of assembling heaps out of the last sites_left
            // sites
            //
            // Select the minimum cost out of folding "folds" sites
            // for 0 <= folds <= sites_left-heaps
            //
            // The cost of each option is the cost of this fold
            // operation plus the cost of assembling the remaining heaps
            // (which is a subproblem I've already solved)
            int current_site = sites-sites_left;
            if(heaps == sites_left || sites_left < 2) {
                // Cruise by the remaining sites
                return 0;
            } else if(heaps == 1) {
                // Gotta take all the heaps to the last site
                return foldCost[current_site][sites_left-1];
            } 
            int mincost = Integer.MAX_VALUE;
            for(int folds=0; folds <= sites_left - heaps; folds++) {
                int newcost = foldCost[current_site][folds]
                    + subproblem[sites_left-folds-1][heaps-1];
                mincost = Math.min(mincost, newcost);
            }
            return mincost;
        }

        public int solve(int nheaps) {
            foldCost = calcFoldCost(nheaps);
            subproblem = new int[sites+1][];
            // Solve the subproblem for 1..sites sites left to visit
            for(int sites_left=1; sites_left<=sites; sites_left++) {
                int max_heaps = Math.min(nheaps, sites_left);
                int current_site = sites-sites_left;
                subproblem[sites_left] = new int[max_heaps + 1];
                // Solve the subproblem for each possible number of heaps desired
                // I can't assemble less than 1 heap
                // I also don't need to assemble less than nheaps-current_site
                // heaps
                for(int heaps = Math.max(1,nheaps-current_site); 
                        heaps <= max_heaps; heaps++) {
                    subproblem[sites_left][heaps] = solveSubproblem(sites_left, 
                            heaps);
                        }
            }
            return subproblem[sites][nheaps];
        }
    }

    public static void main(String[] argv) {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        while(true) {
            try {
                int nsites = sc.nextInt();
                int nheaps = sc.nextInt();
                int[] distance = new int[nsites-1];
                int[] weight = new int[nsites];
                int previous_position = sc.nextInt();
                weight[0] = sc.nextInt();
                for(int site=1; site<nsites; site++) {
                    int position = sc.nextInt();
                    distance[site-1] = position - previous_position;
                    previous_position = position;
                    weight[site] = sc.nextInt();
                }
                System.out.println(new Heaps(distance, weight).solve(nheaps));
            } catch(NoSuchElementException e) {
                // End of input
                break;
            }
        }
    }
}

