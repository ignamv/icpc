#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

const int LETTERS = 26;
const int BUFFER_SIZE = 512;

vector<int> rows(LETTERS);
vector<int> cols(LETTERS);

typedef struct {
    int rows, cols;
    int cost;
} expr;

class MismatchedMatrixException {};

int parse(char *s, expr &dest) {
    if(s[0] >= 'A' && s[0] <= 'Z') {
        dest.rows = rows[s[0]-'A'];
        dest.cols = cols[s[0]-'A'];
        dest.cost = 0;
        return 1;
    }
    int read = 0;
    assert(s[read++] == '(');
    expr left, right;
    read += parse(s+read, left);
    read += parse(s+read, right);
    assert(s[read++] == ')');
    if(left.cols != right.rows) {
        throw MismatchedMatrixException();
    }
    dest.rows = left.rows;
    dest.cols = right.cols;
    dest.cost = left.cost + right.cost + left.rows * right.rows * right.cols;
    return read;
}

int main(int argc, char *argv[]) {
    int nmatrices;
    scanf("%d\n", &nmatrices);
    for(int matrix=0; matrix<nmatrices; matrix++) {
        char mat;
        scanf("%c ", &mat);
        mat -= 'A';
        scanf("%d %d\n", &rows[mat], &cols[mat]);
    }
    char buffer[BUFFER_SIZE];
    while(true) {
        if(scanf("%s\n", buffer) != 1)
            break;
        expr e;
        try {
            parse(buffer, e);
            printf("%d\n", e.cost);
            fflush(stdout);
        } catch(MismatchedMatrixException e) {
            printf("error\n");
        }
    }
    return 0;
}

