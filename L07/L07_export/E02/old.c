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
int diagonaleR(int pos, tabElementi_t val, int *sol, int **b_sol, int k, int *d);
float contaValoreDiag(tabElementi_t tEl, int *diag, int k);
void stampaDiagonale(tabElementi_t tEl, int *diag, int k);
int contaDifficoltaDiag(tabElementi_t tEl, int *diag, int k);
int contaDifficoltaProgr(tabElementi_t tEl, int **prog);
float contaValoreProgr(tabElementi_t tEl, int **prog);
int isElemSequenz(int **prog, int *id);
int isElAvElInd(tabElementi_t tEl, int **prog, int *id);

int main(int argc, char ** argv){
    tabElementi_t tEl = leggiElementi(INPUTFILE_PATH);
    programma(tEl);
    return 0;
}

int programma(tabElementi_t tEl){
    /*int i,d;

    int *programma[MAX_DIAG]; // allocazione vettore di MAX_DIAG puntatori a vettori di interi
    for(i=0;i<MAX_DIAG;i++) malloc(MAX_EL_DIAG*sizeof(int)); // allocazione diagonali (vettore interi)

    for(d=0;d<MAX_DIAG;d++){
        printf("\nDiagonale %d\n",d);
        programma[d] = diagonale(tEl); // alloca e riempie con una soluzione
    }

    */
    int k,i,best_k=0, diff, *d;
    float val;


    // allocazione e inizializzazione matrice programma e best_programma
    int **programma = malloc(MAX_DIAG*sizeof(int *));
    if(programma == NULL) exit(-1);
    int **best_programma = malloc(MAX_DIAG*sizeof(int *));
    if(best_programma == NULL) exit(-1);

    for(i=0;i<MAX_DIAG;i++) {
        programma[i] = malloc(MAX_EL_DIAG * sizeof(int));
        best_programma[i] = malloc(MAX_EL_DIAG * sizeof(int));
        for(k=0;k<MAX_EL_DIAG;k++) {
            programma[i][k] = -1;
            best_programma[i][k] = -1;
        }
    }

    // allocazione e inizializzazione vettore diagonale
    int *diagonale = malloc(MAX_EL_DIAG*sizeof(int));
    for(k=0;i<MAX_EL_DIAG;i++) {
        diagonale[k] = -1;
    }

    // chiamata ricorsiva con k = 1...MAX_EL_DIAG
    *d=0;
    for(k=1;k<=MAX_EL_DIAG;k++){
        diagonaleR(0,tEl,diagonale,programma,k,d);
        val = contaValoreDiag(tEl,programma[*d],k);
        diff = contaDifficoltaDiag(tEl,programma[*d],k);
        if(val > contaValoreDiag(tEl,best_programma[*d],k) && diff < DD) {
            best_k = k;
            for (i = 0; i < k; i++) {
                best_programma[i] = programma[i];
            }
        }
    }
    for(i=0;i<MAX_DIAG;i++){
        printf("\nbest_diagonale per k = %d :\n",best_k);
        printf("punteggio totale: %0.1f\n", contaValoreDiag(tEl,best_programma[i],best_k));
        stampaDiagonale(tEl,best_programma[i],k);
    }

    //

    return 1;
}

/*int *diagonale(tabElementi_t tEl){
    int k,best_k=0,i, diff, *d; *d=0;
    float val;
    int *diagonale = malloc(MAX_EL_DIAG*sizeof(int));
    // int **best_diagonale = malloc(MAX_DIAG*sizeof(int *));
    int **programma = malloc(MAX_DIAG*sizeof(int *));

    for(k=0;i<MAX_EL_DIAG;i++) {
        diagonale[k] = -1;
    }

    for(i=0;i<MAX_DIAG;i++) {
        programma[i] = malloc(MAX_EL_DIAG * sizeof(int));
        for(k=0;i<MAX_EL_DIAG;i++) {
            programma[i][k] = -1;
        }
    }

    // chiamata ricorsiva con k = 1...MAX_EL_DIAG
    for(k=1;k<=MAX_EL_DIAG;k++){
        diagonaleR(0,tEl,diagonale,programma,k,d);

        val = contaValoreDiag(tEl,best_k_diagonale,k);
        diff = contaDifficoltaDiag(tEl,best_k_diagonale,k);
        if(val > contaValoreDiag(tEl,best_diagonale,k) && diff < DD) {
            best_k = k;
            for (i = 0; i < k; i++) {
                best_diagonale[i] = best_k_diagonale[i];
            }
        }
    }
    printf("\nbest_diagonale per k = %d :\n",best_k);
    printf("punteggio totale: %0.1f\n", contaValoreDiag(tEl,best_diagonale,k));
    stampaDiagonale(tEl,best_diagonale,k);
    return programma;

}*/

int diagonaleR(int pos, tabElementi_t tEl, int *sol, int **b_sol, int k, int *d){ // modello disposizioni ripetute
    int i,diff,diff_tot, *id = NULL;
    float val,val_tot;

    // condizione di terminazione
    if(pos >= k && *d==MAX_DIAG-1){ //terminazione ultima diagonale
        val = contaValoreDiag(tEl,sol,k);
        diff = contaDifficoltaDiag(tEl,sol,k);
        // trova soluzione migliore
        if( val > contaValoreDiag(tEl,b_sol[*d],k) && diff < DD){
            for(i=0;i<k;i++){
                b_sol[*d][i] = sol[i];
            }
        }
        return 1;
    }else if(pos >= k){ // terminazione restanti diagonali
        val = contaValoreDiag(tEl,sol,k);
        diff = contaDifficoltaDiag(tEl,sol,k);

        // trova soluzione migliore
        if( val > contaValoreDiag(tEl,b_sol[*d],k) && diff < DD){
            for(i=0;i<k;i++){ // ricopio soluzione migliore trovata
                b_sol[*d][i] = sol[i];
            }
        }
        return 1;
    }

    // RICORSIONE
    if(contaDifficoltaProgr(tEl,b_sol)<DP) { // prooning su difficoltà totale programma
        if (*d == MAX_DIAG - 1) { // ricorsione ultima diagonale
            for (i = 0; i < tEl.n_elementi; i++) {
                if(isElemSequenz(b_sol,id) == 1 || *id == pos-1) { // controllo se ci sono elementi in sequenza nel programma o nel caso se non si sono elementi in sequenza, controllo se posso aggiungerne uno
                   ////// if(isElAvElInd(tEl,b_sol) == 0 || tEl.elementi[i].tipologia == isElAvElInd(tEl,b_sol)){ // controllo se ci c'è almeno un elemento in avanti e uno indietro nel programma e se non c'è vedo se posso metterlo, se no
                        if (pos == 0 && tEl.elementi[i].dir_in == 1) { // inizio diagonale frontalmente
                            if(tEl.elementi[sol[pos-1]].finale == 0) { // controllo se l'elemento precendente non è finale
                                if((sol[pos-1]<0 && tEl.elementi[i].req_prec == 0) || (sol[pos-1]>=0 && tEl.elementi[i].req_prec == 1)) { // controla precedenze
                                    if (tEl.elementi[sol[pos - 1]].dir_out ==
                                        tEl.elementi[i].dir_in) { // direzione in uscita precedente == direzione ingretto corrente
                                        sol[pos] = i;
                                        diagonaleR(pos + 1, tEl, sol, b_sol, k, d);
                                    }
                                }
                            }
                        }
                    //}
                }
            }
            *d++;
        } else { // ricorsione altre diagonali
            for (i = 0; i < tEl.n_elementi; i++) {
                if (pos == 0 && tEl.elementi[i].dir_in == 1) { // inizio diagonale frontalmente
                    if(tEl.elementi[sol[pos-1]].finale == 0){
                        if((sol[pos-1]<0 && tEl.elementi[i].req_prec == 0) || (sol[pos-1]>=0 && tEl.elementi[i].req_prec == 1)) { // controla precedenze
                            if (tEl.elementi[sol[pos - 1]].dir_out ==
                                tEl.elementi[i].dir_in) { // direzione in uscita precedente == direzione ingretto corrente
                                sol[pos] = i;
                                diagonaleR(pos + 1, tEl, sol, b_sol, k, d);
                            }
                        }
                    }
                }
            }
            *d++;
            for (i = 0; i < tEl.n_elementi; i++) {
                if (pos == 0 && tEl.elementi[i].dir_in == 1) { // inizio diagonale frontalmente
                    if(tEl.elementi[sol[pos-1]].finale == 0) { // controllo se l'elemento precendente non è finale
                        if((sol[pos-1]<0 && tEl.elementi[i].req_prec == 0) || (sol[pos-1]>=0 && tEl.elementi[i].req_prec == 1)){ // controla precedenze
                            if (tEl.elementi[sol[pos - 1]].dir_out ==
                                tEl.elementi[i].dir_in) { // direzione in uscita precedente == direzione ingretto corrente
                                sol[pos] = i;
                                diagonaleR(pos + 1, tEl, sol, b_sol, k, d);
                            }
                        }

                    }
                }
            }
            *d++;
        }
    }
    return 1;
}
int isElAvElInd(tabElementi_t tEl, int **prog, int *id){
    int i,j, av=0, in=0;
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_EL_DIAG;j++){
            if(tEl.elementi[prog[i][j]].tipologia == 2) {
                av++;
            }
            if(tEl.elementi[prog[i][j]].tipologia == 1) {
                in++;
            }
        }
    }
    if(av>0 && in>0)
        return 0;
    else if(av>0)
        return 2;
    else if (in>0)
        return 1;
    else
        return -1;
}

int isElemSequenz(int **progr, int *id){
    int i,j;
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_EL_DIAG;j++){
            if(i==MAX_DIAG-1 && j<MAX_EL_DIAG-1){
                *id = j;
            }
            if(progr[i][j]>=0 && progr[i][j-1]>=0) {
                return 1;
            }
        }
    }
    return 0;
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
float contaValoreProgr(tabElementi_t tEl, int **prog){
    int i,j;
    float tot_val=0;
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;i<MAX_EL_DIAG;i++) {
            if (prog[i][j] >= 0) tot_val += tEl.elementi[prog[i][j]].val;
        }
    }
    return tot_val;
}
int contaDifficoltaProgr(tabElementi_t tEl, int **prog){
    int i,j, tot_diff=0;
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_EL_DIAG;j++) {
            if (prog[i][j] >= 0) tot_diff += tEl.elementi[prog[i][j]].difficolta;
        }
    }
    return tot_diff;
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
        printf("\t%d %s %0.2f\n", diag[i], tEl.elementi[diag[i]].nome, tEl.elementi[diag[i]].val);
    }
}