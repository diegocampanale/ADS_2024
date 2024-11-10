#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "grafo.txt"

typedef struct {
    int u; int v;
}arco_t;

typedef struct {
    int n;
    int e;
    arco_t *archi;
}grafo_t;

int powerset(int pos, int *sol, int n, int count, grafo_t gr);
int isVertexCover(int *sol, grafo_t gr);


int main(int argc, char ** argv){
    grafo_t gr;
    int i, n,e, *sol;

    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp,"%d %d\n",&n, &e);
    gr.n = n;
    gr.e = e;
    gr.archi = (arco_t *) malloc(e*sizeof(arco_t));

    for (i=0; i<e; i++){
        fscanf(fp,"%d %d\n",&(gr.archi[i].u), &(gr.archi[i].v));
    }
    sol = calloc(n,sizeof(int));
    int count;

    powerset(0,sol,4,0,gr);
    fclose(fp);

    return 0;
}

int powerset(int pos, int *sol, int n, int count, grafo_t gr){
    int j;

    if (pos >= n) {
        if (isVertexCover(sol,gr)){
            printf("( ");
            for(j=0;j<n;j++){
                if(sol[j] != 0){
                    printf("%d ",j);
                }
            }
            printf(")\n");
        }
        return count+1;
    }

    sol[pos] = 0;
    count = powerset(pos+1,sol,n,count, gr);
    sol[pos] = 1;
    count = powerset(pos+1,sol,n,count,gr);
    return count;
}

int isVertexCover(int *sol, grafo_t gr){
    int i,j, flag = 0;
    for (i=0; i<gr.e; i++){
        flag = 0;
        for(j=0; j<gr.n; j++){
            if(sol[j] == 1 && (gr.archi[i].u == j || gr.archi[i].v == j)){
                flag = 1;
            }
        }
        if (flag == 0) return 0;
    }
    return 1;

}