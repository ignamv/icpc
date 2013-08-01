import java.util.NoSuchElementException;
import java.util.Scanner;
import java.io.BufferedInputStream;

class Main {
    public static void main(String[] argv) {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        int cases = sc.nextInt();
        while(cases-- != 0) {
            // TODO: avoid re-interpreting decimal integer as hex integer
            solve(sc.nextInt());
        }
    }

    static void solve(int input) {
        int dec = input;
        int b1 = 0, b2=0;
        while(dec != 0) {
            b1 += dec & 1;
            dec /= 2;
        }
        // I can count the bits in each hexadecimal digit separately
        // because each hex digit translates to 4 bits
        while(input != 0) {
            int b = input % 10;
            while(b != 0) {
                b2 += b & 1;
                b /= 2;
            }
            input /= 10;
        }
        System.out.printf("%d %d\n",b1,b2);
    }
}
