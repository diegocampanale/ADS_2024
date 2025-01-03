#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "test_set.txt"
#define N_PIETRE 4
#define zaffiro 0
#define  rubino 1
#define topazio 2
#define smeraldo 3

typedef struct{
    int n;
    int n_posizionati;
    int id;
    char nome;
    int val;
    int rip;
}pietra_t;

typedef struct{
    int rip_z;
    int rip_r;
    int rip_t;
    int rip_s;
}ripetizioniR_t; // forse è meglio usare enumerazione e vettore sfruttando come indici i nomi enumerati

int test = 0; // debug
int caso = 0; // debug
int tot = 0; // debug

int disp_rip (int pos, pietra_t *val, int *sol,int max_rip, int max_pos,int val_tot, int val_tot_max, ripetizioniR_t rip, char *bestsol);
void stampa(int *sol,int k){
    for(int i =0; i<k;i++)
        printf("%d ",sol[i]);
    printf("\n");
}
int stampaStruct(pietra_t *pietra){
    int i;
    printf("da posizionare: ");
    for(i=0;i<N_PIETRE;i++){
        printf("%d ",pietra[i].n);
    }
    printf("\n");
    printf("n posizionate: ");
    for(i=0;i<N_PIETRE;i++){
        printf("%d ",pietra[i].n_posizionati);
    }
    printf("\n");
    printf("ripetizioni: ");
    for(i=0;i<N_PIETRE;i++){
        printf("%d ",pietra[i].rip);
    }
    printf("\n");
}

int main(int argc, char ** argv){
    int i, j, n_test, tot_i=0, max_val, max_rip, max_len;
    int *sol;
    char *bestSol;
    pietra_t *pietre;
    ripetizioniR_t rip;

    // allocazione strutture dati
    pietre = malloc(N_PIETRE*sizeof(pietra_t));
    for (i=0;i<N_PIETRE; i++){
        pietre[i].id=i;
        pietre[i].rip=0;
        pietre[i].n_posizionati=0;
    }
    rip.rip_s=0; rip.rip_t=0; rip.rip_r=0; rip.rip_z=0;


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
        for(j=0;j<N_PIETRE;j++) {
            fscanf(fp, "%d ", &pietre[j].val);
        }
        fscanf(fp,"%d\n",&max_rip);

        printf("pietre.n: %d %d %d %d \tpietre.val: %d %d %d %d\n",pietre[0].n, pietre[1].n, pietre[2].n, pietre[3].n, pietre[0].val, pietre[1].val, pietre[2].val, pietre[3].val);
        tot = tot_i; // debug
        sol = malloc(tot_i*sizeof (int));
        bestSol = malloc(tot_i*sizeof (char)+1);
        // inizializzazione vettore soluzioni a -1
        for (j=0;j<tot_i;j++) sol[j] = -1;

        max_val = disp_rip(0,pietre,sol,max_rip,0,0,0,rip,bestSol);
        // printf("TEST #%d\n",i+1); // debug
        // printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",z,r,t,s,tot_i);     // debug
        printf("TEST #%d valore max: %d\n",i+1,max_val);
        printf("BESTSOLLL: %s\n", bestSol);

        free(sol);
        free(bestSol);
    }

    free(pietre);
    fclose(fp);

    return 0;
}

int disp_rip(int pos, pietra_t *val, int *sol, int max_rip, int max_pos,int val_tot, int val_tot_max,ripetizioniR_t rip, char *bestsol){
    int i,j;

    if(pos == 0){
        for(i=0;i<N_PIETRE;i++){
            sol[pos] = i;
            val[i].n--;
            val_tot += val[i].val;

            if(i == zaffiro)
                rip.rip_z++;
            else if(i == rubino)
                rip.rip_r++;
            else if(i == topazio)
                rip.rip_t++;
            else if(i == smeraldo)
                rip.rip_s++;

            // val[i].rip++;
            val[i].n_posizionati++;
            val_tot_max = disp_rip(pos+1,val,sol,max_rip,max_pos,val_tot,val_tot_max,rip,bestsol);
            //val[i].rip--;

            if(i == zaffiro)
                rip.rip_z--;
            else if(i == rubino)
                rip.rip_r--;
            else if(i == topazio)
                rip.rip_t--;
            else if(i == smeraldo)
                rip.rip_s--;

            val[i].n++;
            val[i].n_posizionati--;
            val_tot -= val[i].val;
            sol[pos]=-1;
        }
    }

    /*printf("\ntest: #%d caso: %d pos: %d \t\t \n", test, caso++, pos);
    stampaStruct(val);
    stampa(sol, pos);
    printf("valore collana = %d\n",val_tot);*/


    if(sol[pos-1]==zaffiro || sol[pos-1]==topazio){
        if(val[zaffiro].n>0 && rip.rip_z<max_rip && val[zaffiro].n_posizionati<val[smeraldo].n_posizionati){
            int ns,nt,nr;
            sol[pos]=zaffiro;
            ns = rip.rip_s; nt = rip.rip_t; nr = rip.rip_r;
            rip.rip_s=0; rip.rip_t=0; rip.rip_r=0;
            // if(sol[pos-1]!=sol[pos]) val[sol[pos-1]].rip=0;
            val[zaffiro].n--;
            // val[zaffiro].rip++;
            rip.rip_z++;
            val[zaffiro].n_posizionati++;
            val_tot += val[zaffiro].val;
            val_tot_max = disp_rip(pos+1,val,sol,max_rip,max_pos,val_tot,val_tot_max,rip,bestsol);
            // val[zaffiro].rip=0;
            rip.rip_s = ns; rip.rip_t = nt; rip.rip_r = nr;
            val[zaffiro].n++;
            rip.rip_z--;
            val[zaffiro].n_posizionati--;
            val_tot -= val[zaffiro].val;
            sol[pos]=-1; // debug
        }
        if(val[rubino].n>0 && rip.rip_r<max_rip){
            int ns,nt,nz;

            sol[pos]=rubino;
            ns = rip.rip_s; nt = rip.rip_t; nz = rip.rip_z;
            rip.rip_s=0; rip.rip_t=0; rip.rip_z=0;
            // if(sol[pos-1]!=sol[pos]) val[sol[pos-1]].rip=0;
            val[rubino].n--;
            // val[rubino].rip++;
            rip.rip_r++;
            val[rubino].n_posizionati++;
            val_tot += val[rubino].val;
            val_tot_max = disp_rip(pos+1,val,sol,max_rip,max_pos,val_tot,val_tot_max,rip,bestsol);
            rip.rip_s = ns; rip.rip_t = nt; rip.rip_z = nz;
            val[rubino].n++;
            rip.rip_r--;
            // val[rubino].rip=0;
            val[rubino].n_posizionati--;
            val_tot -= val[rubino].val;
            sol[pos]=-1; // debug
        }

    }else if(sol[pos-1]==rubino || sol[pos-1]==smeraldo){
        if(val[topazio].n>0 && rip.rip_t<max_rip){
            int ns,nr,nz;
            sol[pos]=topazio;
            ns = rip.rip_s; nr = rip.rip_r; nz = rip.rip_z;

            rip.rip_s=0; rip.rip_r=0; rip.rip_z=0;
            // if(sol[pos-1]!=sol[pos]) val[sol[pos-1]].rip=0;
            val[topazio].n--;
            // val[topazio].rip++;
            rip.rip_t++;
            val[topazio].n_posizionati++;
            val_tot += val[topazio].val;
            val_tot_max = disp_rip(pos+1,val,sol,max_rip,max_pos,val_tot,val_tot_max,rip,bestsol);
            val[topazio].n++;
            rip.rip_s = ns; rip.rip_r = nr; rip.rip_z = nz;

            rip.rip_t--;
            val[topazio].n_posizionati--;
            // val[topazio].rip=0;
            val_tot -= val[topazio].val;
            sol[pos]=-1; // debug
        }
        if(val[smeraldo].n>0 && rip.rip_s<max_rip){
            sol[pos]=smeraldo;
            int nz,nr,nt;
            nt = rip.rip_t; nr = rip.rip_r; nz = rip.rip_z;
            rip.rip_t=0; rip.rip_r=0; rip.rip_z=0;
            // if(sol[pos-1]!=sol[pos]) val[sol[pos-1]].rip=0;
            val[smeraldo].n--;
            // val[smeraldo].rip++;
            rip.rip_s++;
            val[smeraldo].n_posizionati++;
            val_tot += val[smeraldo].val;
            val_tot_max = disp_rip(pos+1,val,sol,max_rip,max_pos,val_tot,val_tot_max,rip,bestsol);
            val[smeraldo].n++;
            rip.rip_t = nt; rip.rip_r = nr; rip.rip_z = nz;
            //val[smeraldo].rip=0;
            rip.rip_s--;
            val[smeraldo].n_posizionati--;
            val_tot -= val[smeraldo].val;
            sol[pos]=-1; // debug
        }
    }

    if (val_tot > val_tot_max) {
        val_tot_max = val_tot;
        for(i=0;i<pos;i++){
            switch (sol[i]) {
                case zaffiro:
                    bestsol[i] = 'z';
                    break;
                case rubino:
                    bestsol[i] = 'r';
                    break;
                case topazio:
                    bestsol[i] = 't';
                    break;
                case smeraldo:
                    bestsol[i] = 's';
                    break;

            }
        }
        bestsol[pos] = '\0';
    }

    return val_tot_max;
}