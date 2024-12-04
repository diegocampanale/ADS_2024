#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "elementi.txt"
#define MAXS 100
#define MAX_DIAG 3
#define MAX_EL_DIAG 5
#define DD 10
#define DP 20

typedef struct elemento{
    char nome[MAXS];
    int tipologia, dir_in, dir_out, req_prec, finale, difficolta;
    float val;
}el_t;

typedef struct elementi{
    el_t *elementi;
    int n_elementi;
}tabElementi_t;

tabElementi_t leggiElementi(char *nomefile);
void stampaElementi(tabElementi_t tEl);
int programma(tabElementi_t tEl);
int *diagonale(tabElementi_t tEl);
int diagonaleR(int pos, tabElementi_t val, int *sol, int *b_sol, int k);
float contaValoreDiag(tabElementi_t tEl, int *diag, int k);
void stampaDiagonale(tabElementi_t tEl, int *diag, int k);
int contaDifficoltaDiag(tabElementi_t tEl, int *diag, int k);

int main(int argc, char ** argv){

    tabElementi_t tEl = leggiElementi(INPUTFILE_PATH);
    // stampaElementi(tEl);

    programma(tEl);

    return 0;
}

int programma(tabElementi_t tEl){
    int i,d;

    int *programma[MAX_DIAG];
    for(i=0;i<MAX_DIAG;i++) malloc(MAX_EL_DIAG*sizeof(int));

    for(d=0;d<MAX_DIAG;d++){
        printf("\nDiagonale %d\n",d);
        programma[d] = diagonale(tEl); // alloca e riempie con una soluzione
    }


    return 1;
}

int *diagonale(tabElementi_t tEl){
    int k,i;
    int *diagonale = malloc(MAX_EL_DIAG*sizeof(int));
    int *best_diagonale = malloc(MAX_EL_DIAG*sizeof(int));

    // inizializza vettori diagonali
    for(i=0;i<MAX_EL_DIAG;i++){
        diagonale[i] = -1;
        best_diagonale[i]=-1;
    }

    // chiamata ricorsiva con k = 1...MAX_EL_DIAG
    for(k=1;k<=MAX_EL_DIAG;k++){

        diagonaleR(0,tEl,diagonale,best_diagonale,k);

        printf("\nbest sol per k = %d :\n",k);
        printf("punteggio totale: %0.1f\n", contaValoreDiag(tEl,best_diagonale,k));
        stampaDiagonale(tEl,best_diagonale,k);
    }
}

int diagonaleR(int pos, tabElementi_t tEl, int *sol, int *b_sol, int k){ // modello disposizioni ripetute
    int i;
    float val,diff;
    // condizione di terminazione
    if(pos >= k){
        val = contaValoreDiag(tEl,sol,k);
        diff = contaDifficoltaDiag(tEl,sol,k);

        // trova soluzione migliore
        if( val > contaValoreDiag(tEl,b_sol,k) && diff < DD){
            for(i=0;i<k;i++){
                b_sol[i] = sol[i];
            }
        }
        return 1;
    }

    for(i=0; i<tEl.n_elementi;i++){
        sol[pos] = i;
        diagonaleR(pos+1,tEl,sol,b_sol,k);
    }
    return 1;
}

float contaValoreDiag(tabElementi_t tEl, int *diag, int k){
    int i;
    float tot_val=0;
    for(i=0;i<k;i++){
        if(diag[i]>=0)
            tot_val += tEl.elementi[diag[i]].val;
    }
    return tot_val;
}
int contaDifficoltaDiag(tabElementi_t tEl, int *diag, int k){
    int i, tot_diff=0;
    for(i=0;i<k;i++){
        if(diag[i]>=0)
            tot_diff += tEl.elementi[diag[i]].difficolta;
    }
    return tot_diff;
}
tabElementi_t leggiElementi(char *nomefile){
    int n_el,i;
    tabElementi_t tEl;
    FILE *fp = fopen(nomefile, "r");
    if(fp==NULL) {
        printf("Errore apertura file.\n");
        exit(-1);
    }

    fscanf(fp,"%d\n", &n_el);
    printf("%d\n",n_el);
    tEl.elementi = malloc(n_el*sizeof(el_t));
    for(i=0;i<n_el;i++){
        fscanf(fp," %s %d %d %d %d %d %f %d\n",tEl.elementi[i].nome, &tEl.elementi[i].tipologia, &tEl.elementi[i].dir_in, &tEl.elementi[i].dir_out, &tEl.elementi[i].req_prec, &tEl.elementi[i].finale, &tEl.elementi[i].val, &tEl.elementi[i].difficolta);
    }
    tEl.n_elementi = n_el;
    return tEl;
}
void stampaElementi(tabElementi_t tEl){
    int i;
    for(i=0;i<tEl.n_elementi;i++){
        printf(" %s %d %d %d %d %d %0.1f %d\n",tEl.elementi[i].nome, tEl.elementi[i].tipologia,tEl.elementi[i].dir_in, tEl.elementi[i].dir_out, tEl.elementi[i].req_prec, tEl.elementi[i].finale, tEl.elementi[i].val, tEl.elementi[i].difficolta);
    }
}
void stampaDiagonale(tabElementi_t tEl, int *diag, int k){
    int i;
    for(i = 0; i<k;i++){
        printf("\t%d %s %0.1f\n", diag[i], tEl.elementi[diag[i]].nome, tEl.elementi[diag[i]].difficolta);
    }
}