import java.util.Scanner;


class Heaps {
    public static void main(String[] argv) {
        Scanner sc = new Scanner(System.in);
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
        System.out.println(new Problem(distance, weight).solve(nheaps));
    }

    static class Problem {
        // Distance from this site to the next
        int[] distance;
        // Weight of this site's heap
        int[] weight;
        // Number of sites
        int sites;
        // Cost of sub-problems
        // First index: number of sites to visit. From 1 to sites.
        // Second index: number of heaps to assemble. From 1 to sites_left
        // 1-based indexing for prettier code
        int[][] subproblem;

        public Problem(int[] _distance, int[] _weight) {
            distance = _distance;
            weight = _weight;
            sites = weight.length;
        }

        int[][] calcFoldCost(int nheaps) {
            // Calculate cost of folding j heaps starting from site i
            // Maximum fold length is sites-nheaps
            int[][] ret = new int[sites-1][];
            for(int ii=0; ii<sites-1; ii++) {
                int maxfold = Math.min(sites-ii-1, sites-nheaps);
                ret[ii] = new int[maxfold+1];
                ret[ii][0] = 0;
                int barge_load = weight[ii];
                for(int jj=1; jj<ret[ii].length; jj++) {
                    ret[ii][jj] = ret[ii][jj-1] + barge_load * distance[ii+jj-1];
                    barge_load += weight[ii+jj];
                }
            }
            return ret;
        }

        public int solve(int nheaps) {
            int[][] foldCost = calcFoldCost(nheaps);
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
                // Solve the subproblem for 1..max_heaps heaps desired
                for(int heaps = Math.max(1,nheaps-current_site); heaps <= max_heaps; heaps++) {
                    // Select the minimum cost out of:
                    // - skipping this site (only an option if heaps != 1)
                    // - taking this site's heap to the next site
                    // - taking this site and the next side's heaps to the
                    // following one
                    // - ...
                    // - taking all the heaps from the next (sites_left-heaps)
                    // sites to the next.
                    //
                    // The cost of each option is the cost of the barge
                    // operation plus the cost of doing the rest of the heaps
                    // (which is a subproblem I've already solved)
                    if(heaps == 1) {
                        subproblem[sites_left][heaps] = foldCost[current_site][sites_left-1];
                        continue;
                    }
                    // If heaps > 1 there's always the option of skipping this
                    // site
                    int mincost = subproblem[sites_left-1][heaps-1];
                    // Calculate the cost of 1..(sites_left-heaps) loads
                    for(int loads=1; loads <= sites_left - heaps; loads++) {
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

}
