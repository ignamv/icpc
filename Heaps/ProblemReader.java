import java.util.NoSuchElementException;
import java.util.Scanner;

class ProblemReader {
    public static void main(String[] argv) {
        Scanner sc = new Scanner(System.in);
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

