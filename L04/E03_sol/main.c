#include <stdio.h>
#include <stdlib.h>
#define MAX_PIETRE 4

int test = 0;
int caso = 0;

typedef enum{
    p_zaffiro, p_rubino, p_topazio, p_smeraldo, p_fine
}pietre;

FILE* apri_file(char* text, char* mode);



//
// inizio imponendo un rubino/zaffiro....
// poi continuo la ricorsione forzando solo soluzioni corrette
// con diverse migliaia di gemme crasha lo stack della ricorsione
// ma con 1000 a testa dovrebbe ancora funzionare
//
int combina_pietre_ricorsiva(int pos, int *n_pietre, int *sol, int cnt){
    if(pos==0){
        for(int i=0; i<p_fine; i++){
            sol[pos]=i;
            n_pietre[i]--;
            cnt = combina_pietre_ricorsiva(pos+1, n_pietre, sol, cnt);
            n_pietre[i]++;
        }
        return cnt;
    }

    caso++;
    //printf("test: %d caso: %d \t",test,caso++);
    //for (int i =0; i<pos; i++) printf("%d ",sol[i]);
    //printf("\n");
    if(sol[pos-1]==p_zaffiro || sol[pos-1]==p_topazio){
        if(n_pietre[p_zaffiro]!=0){
            sol[pos]=p_zaffiro;
            n_pietre[p_zaffiro]--;
            cnt = combina_pietre_ricorsiva(pos+1, n_pietre, sol, cnt);
            n_pietre[p_zaffiro]++;
        }
        if (n_pietre[p_rubino]!=0){
            sol[pos]=p_rubino;
            n_pietre[p_rubino]--;
            cnt = combina_pietre_ricorsiva(pos+1, n_pietre, sol, cnt);
            n_pietre[p_rubino]++;
        }
    }

    if(sol[pos-1]==p_smeraldo || sol[pos-1]==p_rubino){
        if(n_pietre[p_smeraldo]!=0){
            sol[pos]=p_smeraldo;
            n_pietre[p_smeraldo]--;
            cnt = combina_pietre_ricorsiva(pos+1, n_pietre, sol, cnt);
            n_pietre[p_smeraldo]++;
        }
        if(n_pietre[p_topazio]!=0){
            sol[pos]=p_topazio;
            n_pietre[p_topazio]--;
            cnt = combina_pietre_ricorsiva(pos+1, n_pietre, sol, cnt);
            n_pietre[p_topazio]++;
        }
    }

    /*if (pos>cnt){
        //printf("Caso: %d\t",caso);
        for (int i =0; i<cnt; i++) printf("%d ",sol[i]);
        printf("\n");
    }*/

    return (pos>cnt) ? pos : cnt ;
}


int sum(int *v, int dim_v){
    int summ=0;
    for(int i=0; i<dim_v; i++)
        summ+=v[i];
    return summ;
}



int main() {
    FILE *fin= apri_file("inserire il nome del file da aprire", "r");
    int iterazioni, n_pietre[4], len_max_collana, lunghezza=0;
    fscanf(fin, "%d", &iterazioni);
    while(iterazioni!=0){
        iterazioni--;
        fscanf(fin, "%d %d %d %d", &n_pietre[p_zaffiro], &n_pietre[p_rubino],&n_pietre[p_topazio],&n_pietre[p_smeraldo]);
        len_max_collana=sum(n_pietre, MAX_PIETRE);
        //vettore per calcolo di soluzioni
        int sol[len_max_collana];

        test++;
        lunghezza= combina_pietre_ricorsiva(0, n_pietre, sol, 0);
        printf("test: %d lunghezza max: %d\n", 15-iterazioni,lunghezza);
    }

    return 0;
}


FILE* apri_file(char* text, char* mode){
    char file_name[50];
    FILE *fin=NULL;

    while(fin==NULL){
        printf("%s\n", text);
        scanf("%s", file_name);
        fin= fopen(file_name, mode);

    }
    return fin;
}