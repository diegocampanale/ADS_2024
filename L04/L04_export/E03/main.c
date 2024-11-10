#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "easy_test_set.txt"
#define N_PIETRE 4
#define zaffiro 0
#define  rubino 1
#define topazio 2
#define smeraldo 3

typedef struct{
    int n;
    int id;
    char nome;
}pietra_t;

int test = 0; // debug
int caso = 0; // debug
int tot = 0; // debug

int disp_rip (int pos, pietra_t *val, int *sol, int max_pos);
void stampa(int *sol,int k){
    for(int i =0; i<k;i++)
        printf("%d ",sol[i]);
    printf("\n");
}

int main(int argc, char ** argv){
    int i, j, n_test, tot_i=0, max_len;
    int *sol;
    pietra_t *pietre;

    // allocazione strutture dati
    pietre = malloc(N_PIETRE*sizeof(pietra_t));
    for (i=0;i<N_PIETRE; i++){
        pietre[i].id=i;
    }

    // lettura file e inizializzazione strutture dati
    FILE *fp = fopen(INPUTFILE_PATH,"r");
    fscanf(fp,"%d\n",&n_test);

    for(i=0; i<n_test;i++){
        test++;
        caso=0;

        for(j=0;j<N_PIETRE;j++) {
            fscanf(fp, "%d ", &pietre[j].n);
            tot_i +=pietre[j].n;
        }
        // printf("pietre.n: %d %d %d %d\n",pietre[0].n, pietre[1].n, pietre[2].n, pietre[3].n);
        tot = tot_i; // debug
        fscanf(fp,"\n");
        sol = malloc(tot_i*sizeof (int));
        // inizializzazione vettore soluzioni a -1
        for (j=0;j<tot_i;j++) sol[j] = -1;

        max_len = disp_rip(0,pietre,sol,0);
        // printf("TEST #%d\n",i+1); // debug
        // printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",z,r,t,s,tot_i);     // debug
        printf("TEST #%d lunghezza max: %d\n",i+1,max_len);

        free(sol);
        free(pietre);
    }

    fclose(fp);

    return 0;
}

int disp_rip(int pos, pietra_t *val, int *sol, int max_pos){
    int i;

    //printf("test: %d caso: %d pos: %d \t occ: %d %d %d %d  \t\t", test, caso++, pos, val[0].n, val[1].n, val[2].n, val[3].n,pos);
    // stampa(sol, tot);

    if(pos == 0){
        for(i=0;i<N_PIETRE;i++){
            sol[pos] = i;
            val[i].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[i].n++;
            sol[pos]=-1;
        }
    }

     //printf("test: %d caso: %d pos: %d \t\t occ: %d %d %d %d  \t\t", test, caso++, pos, val[0].n, val[1].n, val[2].n, val[3].n);
      //stampa(sol, pos);


    if(sol[pos-1]==zaffiro || sol[pos-1]==topazio){
        if(val[zaffiro].n>0){
            sol[pos]=zaffiro;
            val[zaffiro].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[zaffiro].n++;
            sol[pos]=-1; // debug

        }
        if(val[rubino].n>0){
            sol[pos]=rubino;
            val[rubino].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[rubino].n++;
            sol[pos]=-1; // debug
        }

    }else if(sol[pos-1]==rubino || sol[pos-1]==smeraldo){
        if(val[topazio].n>0){
            sol[pos]=topazio;
            val[topazio].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[topazio].n++;
            sol[pos]=-1; // debug
        }
        if(val[smeraldo].n>0){
            sol[pos]=smeraldo;
            val[smeraldo].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[smeraldo].n++;
            sol[pos]=-1; // debug
        }
    }/*else if(sol[pos-1]==2){
        if(val[0].n>0){
            sol[pos]=0;
            val[0].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[0].n++;
            sol[pos]=-1;

        }
        if(val[1].n>0){
            sol[pos]=1;
            val[1].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[1].n++;
            sol[pos]=-1;
        }
    }else if(sol[pos-1]==3){
        if(val[2].n>0){
            sol[pos]=2;
            val[2].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[2].n++;
            sol[pos]=-1;

        }
        if(val[3].n>0){
            sol[pos]=3;
            val[3].n--;
            max_pos = disp_rip(pos+1,val,sol,max_pos);
            val[3].n++;
            sol[pos]=-1;

        }
    }*/

    if (pos > max_pos) max_pos = pos;

    return max_pos;
}