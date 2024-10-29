#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUTFILE_PATH "brani.txt"
#define MAXR 255

typedef struct {
    int num_scelte;
    char **scelte;
}amico;

int princ_molt(int pos, amico *val, int *sol, int n, int count);


int main(int argc, char ** argv){
    int n_amici, i,j,n_songs=0, cnt;
    char riga[255];
    amico *amici;

    int *sol;

    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp,"%d\n", &n_amici);

    amici = (amico *) malloc(n_amici*sizeof (amico));
    if (amici == NULL) exit(1);

    for(i=0; i<n_amici; i++){
        fscanf(fp,"%d\n", &amici[i].num_scelte);
        amici[i].scelte = (char **) malloc(amici[i].num_scelte*sizeof (char *));
        if (amici[i].scelte == NULL) exit(1);

        for(j=0; j<amici[i].num_scelte; j++){
            amici[i].scelte[j] = (char *) malloc(MAXR*sizeof (char));
            fgets(riga, MAXR, fp);
            sscanf(riga, "%s", amici[i].scelte[j]);
            // printf("canzone %d: %s\n",j,amici[i].scelte[j]);
        }
    }
    sol = (int *) malloc(n_amici*sizeof (int));

    printf("Le possibili playlist generate sono le seguenti : \n");
    cnt = princ_molt(0, amici, sol, n_amici,0);
    printf("e in totale sono %d \n", cnt);

    // FREE;
    free(sol);
    for (i = 0; i < n_amici; i++) {
        for (j = 0; j < amici[i].num_scelte; j++) {
            free(amici[i].scelte[j]);
        }
        free(amici[i].scelte);
    }
    free(amici);

    fclose(fp);

    return 0;
}

// F1nzione ricorsiva per generare tutte le combinazioni di playlist
int princ_molt(int pos, amico *val, int *sol, int n, int count) {
    int i,pos_i;

    if (pos >= n) {
        for (pos_i = 0; pos_i<n; pos_i++) {
            printf("%s ", val[pos_i].scelte[sol[pos_i]]);
        }
        printf("\n");
        return count+1;
    }

    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] = i;
        count = princ_molt(pos + 1, val, sol, n,count);
    }
    return count;
}

