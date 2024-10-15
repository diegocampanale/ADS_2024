#include <stdio.h>

#define INPUTFILE_PATH "/Users/diegocampanale/CLionProjects/ASD_24/L02/E02/mat.txt"

void separa(int **mat, int nr, int nc );

int main(int argc, char ** argv){
    int nr, nc, i;
    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp, "%d %d ", &nr, &nc);
    printf("%d %d ", nr, nc);
    for (i = 0; i<nr; i++){

    }

    return 0;
}
