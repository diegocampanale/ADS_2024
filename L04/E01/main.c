#include <stdio.h>

#define INPUTFILE_PATH "grafo.txt"

typedef struct {
    int u; int v;
}arco_t;

typedef struct {
    int n;
    arco_t *archi;
}grafo_t;

int main(int argc, char ** argv){
    grafo_t gr;
    int i;

    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp,"%d",&i);
    printf("%d\n",i);

    fclose(fp);

    return 0;
}
