#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "elementi.txt"
#define MAXS 100
#define MAX_DIAG 3
#define MAX_EL_DIAG 5
#define DD 40
#define DP 100

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
// int *diagonale(tabElementi_t tEl);
void diagonaleR(int pos, tabElementi_t tEl, int *sol, int *b_sol, int k, int *best_k);
float contaValoreDiag(tabElementi_t tEl, int *diag, int k);
void stampaDiagonale(tabElementi_t tEl, int *diag, int k);
int contaDifficoltaDiag(tabElementi_t tEl, int *diag, int k);
int contaDifficoltaProgr(tabElementi_t tEl, int **prog);
float contaValoreProgr(tabElementi_t tEl, int **prog);
int isElemSequenz(int **prog, int *id);
int isElAvElInd(tabElementi_t tEl, int **prog, int *id);

void programmaR(int pos, tabElementi_t tEl, int **sol, int **best_sol, int *diagonale,int d, int *curr_k,int *best_k);
int condizioniProgramma(tabElementi_t tEl, int **prog, int **best_prog, int *curr_k, int *best_k);
int condizioniDiagonale(tabElementi_t tEl,int *diag, int *best_diag,int k, int best_k);
int prooningDiagonale(tabElementi_t tEl, int *sol,int pos,int i,int k);

int main(int argc, char ** argv){
    tabElementi_t tEl = leggiElementi(INPUTFILE_PATH);
    programma(tEl);
    return 0;
}

int programma(tabElementi_t tEl){
    int k,d,i;

    // allocazione e inizializzazione matrice programma e best_programma
    int **programma = malloc(MAX_DIAG*sizeof(int *));
    if(programma == NULL) exit(-1);
    int **best_programma = malloc(MAX_DIAG*sizeof(int *));
    if(best_programma == NULL) exit(-1);

    for(d=0;d<MAX_DIAG;d++) {
        programma[d] = malloc(MAX_EL_DIAG * sizeof(int));
        best_programma[d] = malloc(MAX_EL_DIAG * sizeof(int));
        for(k=0;k<MAX_EL_DIAG;k++) {
            programma[d][k] = -1;
            best_programma[d][k] = -1;
        }
    }

    // allocazione e inizializzazione vettore diagonale
    int *diagonale = malloc(MAX_EL_DIAG*sizeof(int));
    for(k=0;k<MAX_EL_DIAG;k++) {
        diagonale[k] = -1;
    }

    // allocazione vettori di lunghezze diagonali
    int *best_k = malloc(MAX_DIAG*sizeof(int));
    int *curr_k = malloc(MAX_DIAG*sizeof(int));
    for(d=0;d<MAX_DIAG;d++) {
        curr_k[d] = -1;
        best_k[d] = -1;
    }

    programmaR(0,tEl,programma,best_programma,diagonale,MAX_DIAG,curr_k,best_k);

    printf("Programma senza vincoli:\n");
    for(d=0;d<MAX_DIAG;d++){
        printf("Diagonale #%d   k = %d \n",d,best_k[d]);
        stampaDiagonale(tEl,best_programma[d],MAX_EL_DIAG);
        printf("Val diagonale: %0.2f", contaValoreDiag(tEl,best_programma[d],best_k[d]));
        printf("\n");
    }

    free(best_k);
    free(curr_k);
    free(diagonale);
    for(d=0;d<MAX_DIAG;d++){
        free(programma[d]);
        free(best_programma[d]);
    }
    free(programma);
    free(best_programma);
    return 1;
}

void stampaSol(int** sol){
    int i,j;
    printf("sol:\n");
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_EL_DIAG;j++){
            printf("%d ",sol[i][j]);
        }
        printf("\n");
    }
}

// da allocare : diagonale, sol(matrice temporanea), best_sol(matrice finale), best_k, k
void programmaR(int pos, tabElementi_t tEl, int **sol, int **best_sol, int *diagonale,int d, int *curr_k,int *best_k){
    int i,j,k,e;
    float val_tot = 0, best_val_tot=0;

    stampaSol(sol);

    // terminazione
    if(pos>=d){

        printf("Terminazione\n");

        /*int ok_diag=0;
        for(i=0;i<MAX_DIAG;i++){
            if(condizioniDiagonale(tEl,sol[i],best_sol[i],curr_k[i],best_k[i])){
                ok_diag++;
            }
        }*/
        //if(ok_diag==MAX_DIAG && condizioniProgramma(tEl,sol,best_sol,curr_k,best_k)==1){

            /*printf("best_sol:\n");
            for(i=0;i<MAX_DIAG;i++){
                for(j=0;j<MAX_EL_DIAG;j++){
                    printf("%d ",best_sol[i][j]);
                }
                printf("\n");
            }
            printf("\n");*/

            /*
            for(i=0;i<MAX_DIAG;i++){
                for(j=0;j<MAX_EL_DIAG;j++){
                    best_sol[i][j] = sol[i][j];
                }
                best_k[i] = curr_k[i];
            }*/
        //}

        return;
    }

    int p;
    // Ricorsione programmaR
    for(i=0;i<d;i++){
        for(k=MAX_EL_DIAG;k>0;k--){
            for(j=0;j<k;j++){
                for (e = 0; e < tEl.n_elementi; e++) {
                    if (prooningDiagonale(tEl,sol[pos],j,e,k)==1){
                        sol[pos][j] = e;
                        stampaSol(sol);
                        programmaR(pos + 1, tEl, sol, best_sol,diagonale,d,curr_k,best_k);
                        //sol[pos][j] = -1;
                    }
                }
            }
            for(p=0;p<k;p++){
                sol[pos][p] = -1;
            }
        }


        /*for (i = 0; i < tEl.n_elementi; i++) {
            //if (prooningDiagonale(tEl,sol[pos],pos_i,i,k)==1){
                sol[pos][pos_i] = i;
                programmaR(pos + 1,pos_i, tEl, sol, best_sol,diagonale,d,curr_k,best_k);

            //}
        }*/

        //diagonaleR(0, tEl, diagonale, sol[pos],k,&curr_k[pos]);
        //printf("Diagonale migliore fin ora con k=%d e punt:%0.2f\n",k, contaValoreDiag(tEl,sol[pos],curr_k[pos]));
        //stampaDiagonale(tEl,sol[pos],MAX_EL_DIAG);
        //programmaR(pos+1,tEl,sol,best_sol,diagonale,d,curr_k,best_k);

    }
}

void diagonaleR(int pos, tabElementi_t tEl, int *sol, int *b_sol, int k, int *best_k){ // modello disposizioni ripetute
    int i;

    /*
    printf("sol:       ");
    for(i=0;i<MAX_EL_DIAG;i++){
        printf("%d ",sol[i]);
    }
    printf("     p: %0.2f\n", contaValoreDiag(tEl,sol,k));
    printf("best_sol:  ");
    for(i=0;i<MAX_EL_DIAG;i++){
        printf("%d ",b_sol[i]);
    }
    printf("     p: %0.2f\n", contaValoreDiag(tEl,b_sol,*best_k));
*/

    if(pos >= k){ // terminazione
        //if(condizioniDiagonale(tEl,sol,b_sol,k,*best_k)){
            *best_k = k;
            for(i=0;i<k;i++){ // ricopio soluzione migliore trovata
                b_sol[i] = sol[i];
            }
        //}
        return;
    }

    // RICORSIONE
    for (i = 0; i < tEl.n_elementi; i++) {
        if (prooningDiagonale(tEl,sol,pos,i,k)==1){
            sol[pos] = i;
            diagonaleR(pos + 1, tEl, sol, b_sol, k,best_k);
        }
    }
    return;
}

int prooningDiagonale(tabElementi_t tEl, int *sol,int pos, int i,int k){

    // inizio diagonale frontalmente
    if(pos==0 && tEl.elementi[i].dir_in!=1){
        return 0;
    }

    // controllo se l'elemento precendente non è finale
    if(tEl.elementi[sol[pos-1]].finale == 1) {
        return 0;
    }

    // controla precedenze
    if((pos==0 && tEl.elementi[i].req_prec != 0) || (pos>1 && sol[pos-1]>=0 && tEl.elementi[i].req_prec == 0)) {
        return 0;
    }

    // direzione in uscita precedente == direzione ingretto corrente
    if (pos>0 && tEl.elementi[sol[pos - 1]].dir_out != tEl.elementi[i].dir_in) {
        return 0;
    }

    // controlla che l'aggiunta dell'elemento non oltrepassi il limite difficoltà
    int diff_diag = contaDifficoltaDiag(tEl,sol,k);
    if(diff_diag + tEl.elementi[i].difficolta > DD) {
        return 0;
    }

    return 1;
}

int condizioniProgramma(tabElementi_t tEl, int **prog, int **best_prog, int *curr_k, int *best_k){
    int i,j;

    // controllo valore corrente migliore dell'best_programma
    float val_tot=0,best_val_tot=0;
    int isDiff8=0;
    for(j=0;j<MAX_EL_DIAG;j++){
        if(prog[MAX_DIAG-1][j]>=0 && tEl.elementi[prog[MAX_DIAG-1][j]].difficolta == 8 && tEl.elementi[prog[MAX_DIAG-1][j]].finale == 1)
            isDiff8 = 1;
    }
    for(i=0;i<MAX_DIAG;i++){
        if(i==MAX_DIAG-1 && isDiff8==1){
            val_tot += contaValoreDiag(tEl, prog[i],curr_k[i])*1.5;
            best_val_tot += contaValoreDiag(tEl, best_prog[i],best_k[i])*1.5;
        }else{
            val_tot += contaValoreDiag(tEl, prog[i],curr_k[i]);
            best_val_tot += contaValoreDiag(tEl, best_prog[i],best_k[i]);
        }

    }
    if(val_tot<=best_val_tot) return 0;

    // controllo inclusione elemento in avanti e elemento indietro nella soluzione programma
    int cntAvanti = 0, cntIndietro = 0;
    for(i=0;i<MAX_DIAG && !(cntAvanti && cntIndietro);i++){
        for (j=0;j<MAX_EL_DIAG && !(cntAvanti && cntIndietro);j++){
            if(prog[i][j]>=0){
                if(tEl.elementi[prog[i][j]].tipologia == 2) cntAvanti=1;
                if(tEl.elementi[prog[i][j]].tipologia == 1) cntIndietro=1;
            }
        }
    }
    if(cntAvanti==0 || cntIndietro == 0) return 0;

    // controllo che almeno una diagonale abbia almeno due elementi acrobatici in sequenza
    int ok=0;
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_EL_DIAG;j++){
            if(prog[i][j]>=0 && prog[i][j-1]>=0 && tEl.elementi[prog[i][j]].dir_in == tEl.elementi[prog[i][j-1]].dir_out) {
                ok=1;
            }
        }
    }
    if(ok == 0) return 0;

    // controllo difficoltà totale programma minore o uguale a DP
    int diff_tot=0;
    for(i=0;i<MAX_DIAG;i++){
        diff_tot += contaDifficoltaDiag(tEl,prog[i],curr_k[i]);
    }
    if(diff_tot>DP) return 0;

    return 1;
}

int condizioniDiagonale(tabElementi_t tEl,int *diag, int *best_diag,int k, int best_k){
    int i;

    // miglioramento soluzione ottima
    if(contaValoreDiag(tEl,diag,k) <= contaValoreDiag(tEl,best_diag,best_k)){
        return 0;
    }

    // controllo difficolta diagonale
    int diff_tot=0;
    for(i=0;i<k;i++){
        diff_tot += contaDifficoltaDiag(tEl,diag,k);
    }
    if(diff_tot>DD) return 0;

    return 1;
}

float contaValoreDiag(tabElementi_t tEl, int *diag, int k){
    int i;
    float tot_val=0;
    for(i=0;i<k;i++){
        if(diag[i]>=0) {
            tot_val += tEl.elementi[diag[i]].val;
        }
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
    tEl.elementi = malloc(n_el*sizeof(el_t));
    for(i=0;i<n_el;i++){
        fscanf(fp," %s %d %d %d %d %d %f %d\n",tEl.elementi[i].nome, &tEl.elementi[i].tipologia, &tEl.elementi[i].dir_in, &tEl.elementi[i].dir_out, &tEl.elementi[i].req_prec, &tEl.elementi[i].finale, &tEl.elementi[i].val, &tEl.elementi[i].difficolta);
    }
    tEl.n_elementi = n_el;
    return tEl;
}
void stampaDiagonale(tabElementi_t tEl, int *diag, int k){
    int i;
    for(i = 0; i<k;i++){
        printf("\t%d %s %0.2f\n", diag[i], tEl.elementi[diag[i]].nome, tEl.elementi[diag[i]].val);
    }
}