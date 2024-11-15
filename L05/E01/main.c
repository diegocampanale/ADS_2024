#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "att.txt"

typedef struct{
    int s;
    int f;
}att;

void attSel(int N, att *v); // wrapper
void attSelR(int pos, att *val, int *sol, int n, int k, int start, int *best_sol, int *max_durata, int *nb_sol);
int isCompatibile(att *v, int *sol, int pos);
int calcolaDurata(att *v, int *sol, int pos);
void stampaAttivita(int n, int *sol, att*v);

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

    attSel(n_att, attivita); // chiamata wrapper

    free(attivita);
    return 0;
}

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
    printf("Attività compatibili con durata massima %d: ",max_durata);
    stampaAttivita(nb_sol,b_sol,v);

    free(b_sol);
    free(sol);
}

void attSelR(int pos, att *val, int *sol, int n, int k, int start, int *best_sol, int *max_durata, int *nb_sol){ // modello combinazioni semplici con k variabile da 1 a N-1
    int i,durata_curr;

    if(pos>=k){
        if (isCompatibile(val,sol,pos)){ // cond di accettazione
            durata_curr = calcolaDurata(val,sol,pos);
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

int isCompatibile(att *v, int *sol, int pos){
    int i;
    for(i=0; i<pos-1;i++){
        if (v[sol[i]].f > v[sol[i+1]].s)
            return 0;
    }
    return 1;
}

int calcolaDurata(att *v, int *sol, int pos){
    int i, durata = 0;
    for(i=0; i<pos;i++){
        durata += v[sol[i]].f - v[sol[i]].s;
    }
    return durata;
}

void stampaAttivita(int n, int *sol, att*v){
    int i;
    for(i=0; i<n; i++){
        printf("( %d,%d ) ", v[sol[i]].s, v[sol[i]].f);
    }
    printf("\n");
}