#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "att2.txt"

typedef struct{
    int s;
    int f;
}att;

// prototipi funzioni Soluzione Ricorsiva
void attSel(int N, att *v);
void attSelR(int pos, att *val, int *sol, int n, int k, int start, int *best_sol, int *max_durata, int *nb_sol);
int isCompatibileSol(att *v, int *sol, int pos);
int calcolaDurataSol(att *v, int *sol, int pos);
void stampaAttivita(int n, int *sol, att*v);

// Prototipi funzioni Programmazione Dinamica
void attSelDP(int N, att *val);
void attSelDPOld(int N, att *val);
void mergeSort(att *A, int *B, int N);
void MergeSortR(att *A, int *B, int l, int r);
void Merge(att *A, int *B, int l, int q, int r);
int calcolaDurataAtt(att a);
int isCompatibile(att a, att b);
void displaySol(att *val, int *sol,int *comp,int *ord, int N);

int main(int argc, char ** argv){

    // Dichiarazione
    att *attivita;
    int n_att,i;

    // lettura file
    FILE *fin = fopen(INPUTFILE_PATH,"r");
    if(fin==NULL){
        printf("Errore apertura file.\n");
        exit(-1);
    }
    fscanf(fin,"%d\n",&n_att);

    //Allocazione e inizializzazione
    attivita = (att *) malloc(n_att*sizeof(att));
    for(i=0; i<n_att;i++){
        fscanf(fin,"%d %d\n",&attivita[i].s, &attivita[i].f);
    }
    fclose(fin);

    attSel(n_att, attivita);
    attSelDP(n_att,attivita);

    free(attivita);
    return 0;
}
void attSelDP(int N, att *val){
    int *sol, *ord, *comp;
    int i,j;

    sol = (int *)calloc(N,sizeof(int));
    ord = (int *)calloc(N,sizeof(int));
    comp = (int *)calloc(N,sizeof(int));

    mergeSort(val,ord,N); // ordina per tempo fine attività

    for(i=0;i<N;i++) {
        comp[i] = -1;
    }

    // compatibilità
    comp[ord[0]] = -1;
    for(i=1;i<N;i++){
        for(j=0;j<i;j++){
            if(isCompatibile(val[ord[j]],val[ord[i]])){
                comp[ord[i]] = j;
            }
        }
    }

    // primo elemento preso
    sol[ord[0]]= calcolaDurataAtt(val[ord[0]]);
    for(i=1;i<N;i++){
        if(sol[i-1] < calcolaDurataAtt(val[ord[i]]) + sol[comp[ord[i]]] ){
            sol[i] = calcolaDurataAtt(val[ord[i]]) + sol[comp[ord[i]]];
        }else{
            sol[i] = sol[i-1];
        }
    }

    printf("Soluzione Programmazione dinamica:\n");
    printf("Attività compatibili con durata massima %d:\n", sol[N-1]);
    displaySol(val,sol,comp,ord,N);

}
void displaySol(att *val, int *opt,int *comp,int *ord, int N){
    int i, *sol, ultimo=-1;
    sol = calloc(N,sizeof(int));


    for(i=N-2;i>=0 && ultimo<0;i--){
        if(opt[i]!=opt[i+1]){
            ultimo = ord[i+1];
        }
    }

    sol[ultimo] = 1;
    i=ultimo;
    while(i>=0){
        i = comp[ord[i]];
        sol[i] = 1;
    }

    for(i=0;i<N;i++){
        if(sol[i]){
            printf("( %d,%d )",val[ord[i]].s,val[ord[i]].f);
        }
    }
    printf("\n");
}
int isCompatibile(att a, att b){
    return (a.f<=b.s);
}
int calcolaDurataAtt(att a){
    return (a.f-a.s);
}
void mergeSort(att *A, int *B, int N){
    for (int i = 0; i < N; i++) {
        B[i] = i; // Popola B con gli indici da 0 a N-1
    }
    int l=0, r=N-1;
    MergeSortR(A,B,l,r);
}
void MergeSortR(att *A, int *B, int l, int r){
    int q;
    if(l>=r)
        return;
    q = (l+r)/2;
    MergeSortR(A,B,l,q);
    MergeSortR(A,B,q+1,r);
    Merge(A,B,l,q,r);
}
void Merge(att *A, int *B, int l, int q, int r) {
    int i = l, j = q + 1, k = 0;
    int *tempB = malloc((r - l + 1) * sizeof(int)); // Array temporaneo

    while (i <= q && j <= r) {
        if (A[B[i]].f < A[B[j]].f) {
            tempB[k++] = B[i++];
        } else if (A[B[i]].f > A[B[j]].f) {
            tempB[k++] = B[j++];
        } else {
            // In caso di parità, ordina per tempo di inizio decrescente
            if (A[B[i]].s > A[B[j]].s) {
                tempB[k++] = B[i++];
            } else {
                tempB[k++] = B[j++];
            }
        }
    }

    while (i <= q) {
        tempB[k++] = B[i++];
    }

    while (j <= r) {
        tempB[k++] = B[j++];
    }

    // Copia i risultati nell'array originale B
    for (k = 0; k <= r - l; k++) {
        B[l + k] = tempB[k];
    }

    free(tempB); // Libera la memoria
}

// funzioni Soluzione Ricorsiva (E01 L05)
void attSel(int N, att *v){ // wrapper
    int *sol, *k_b_sol,*b_sol;
    int k,i,k_max_durata = 0, k_nb_sol, nb_sol, max_durata=0;

    // Allocazione vettori soluzioni
    k_b_sol = (int *) malloc(N*sizeof(int));
    b_sol = (int *) malloc(N*sizeof (int));
    sol = (int *) malloc(N*sizeof(int));

    for(k=1; k<N; k++){
        attSelR(0,v,sol,N,k,0,k_b_sol,&k_max_durata,&k_nb_sol);

        // aggiorna soluzione ottimale
        if(k_max_durata>max_durata){
            max_durata = k_max_durata;
            nb_sol = k_nb_sol;
            for(i=0;i<nb_sol;i++){
                b_sol[i]=k_b_sol[i];
            }
        }
    }
    // stampa soluzione ottimale
    printf("Soluzione ricorsiva:\n");
    printf("Attività compatibili con durata massima %d: ",max_durata);
    // stampaAttivita(nb_sol,b_sol,v);
    printf("\n");

    free(b_sol);
    free(sol);
}
void attSelR(int pos, att *val, int *sol, int n, int k, int start, int *best_sol, int *max_durata, int *nb_sol){ // modello combinazioni semplici con k variabile da 1 a N-1
    int i,durata_curr;

    if(pos>=k){
        if (isCompatibileSol(val,sol,pos)){ // cond di accettazione
            durata_curr = calcolaDurataSol(val,sol,pos);
            if( durata_curr > *max_durata){ // cond di ottimalità
                *max_durata = durata_curr;
                *nb_sol = pos;
                for(i=0; i<pos;i++){
                    best_sol[i] = sol[i];
                }
            }
        }
        return;
    }

    for(i=start; i<n; i++){
        sol[pos] = i;
        attSelR(pos+1,val,sol,n,k,i+1, best_sol, max_durata, nb_sol);
    }
}
int isCompatibileSol(att *v, int *sol, int pos){
    int i;
    for(i=0; i<pos-1;i++){
        if (v[sol[i]].f > v[sol[i+1]].s)
            return 0;
    }
    return 1;
}
int calcolaDurataSol(att *v, int *sol, int pos){
    int i, durata = 0;
    for(i=0; i<pos;i++){
        durata += v[sol[i]].f - v[sol[i]].s;
    }
    return durata;
}
void stampaAttivita(int n, int *sol, att*v){
    int i;
    printf("\n");
    for(i=0; i<n; i++){
        printf("( %d,%d ) ", v[sol[i]].s, v[sol[i]].f);
    }
    printf("\n");
}