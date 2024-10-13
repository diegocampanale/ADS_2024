#include <stdio.h>

#define INPUTFILE_PATH "./mat.txt"

void separa(int **mat, int nr, int nc );

int main(int argc, char ** argv){
    int nr, nc, i;
    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp, "%d %d ", &nr, &nc); // read row, col
    for (i = 0; i<nr; i++){

    }

    return 0;
}
