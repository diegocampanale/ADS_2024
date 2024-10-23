#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUTFILE_PATH "brani.txt"
#define MAXR 255

typedef struct {
    int num_scelte;
    int *scelte;
}Livello;

int princ_molt(int pos, Livello *val, int *sol, int n, int count, char ***songs);


int main(int argc, char ** argv){
    int n_amici, i,j,n_songs=0, cnt;
    char riga[255], ***proposte;
    Livello *valor;

    int *sol;

    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp,"%d\n", &n_amici);

    proposte = (char ***) malloc(n_amici*sizeof (char**));
    valor = (Livello *) malloc(n_amici*sizeof (Livello));
    if (proposte == NULL || valor == NULL) exit(1);

    for(i=0; i<n_amici; i++){
        fscanf(fp,"%d\n", &valor[i].num_scelte);
        valor[i].scelte = (int *) malloc(valor[i].num_scelte * sizeof(int));
        proposte[i] = (char **) malloc(valor[i].num_scelte*sizeof (char *));
        if (proposte[i] == NULL || valor[i].scelte == NULL) exit(1);

        for(j=0; j<valor[i].num_scelte; j++){
            proposte[i][j] = (char *) malloc(MAXR*sizeof (char));
            fgets(riga, MAXR, fp);
            sscanf(riga, "%s", proposte[i][j]);
            valor[i].scelte[j] = j;
            // printf("canzone %d: %s\n",valor[i].scelte[j],amici[i].proposte[j]);
        }
    }
    sol = (int *) malloc(n_amici*sizeof (int));

    printf("Le possibili playlist generate sono le seguenti : \n");
    cnt = princ_molt(0, valor, sol, n_amici,0,proposte);
    printf("e in totale sono %d \n", cnt);

    // FREE;
    free(sol);
    for (i = 0; i < n_amici; i++) {
        for (j = 0; j < valor[i].num_scelte; j++) {
            free(proposte[i][j]);
        }
        free(valor[i].scelte);
        free(proposte[i]);
    }
    free(valor);
    free(proposte);

    fclose(fp);

    return 0;
}

// F1nzione ricorsiva per generare tutte le combinazioni di playlist
int princ_molt(int pos, Livello *val, int *sol, int n, int count, char ***songs) {
    int i;

    if (pos >= n) {
        for (i = 0; i<n; i++) {
            printf("%s ", songs[i][sol[i]]);
        }
        printf("\n");
        return count+1;
    }

    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos + 1, val, sol, n,count, songs);
    }
    return count;
}

