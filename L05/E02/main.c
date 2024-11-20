#include <stdio.h>
#include <stdlib.h>

#define INPUT_BOARD "board2.txt"
#define INPUT_TILES "tiles.txt"

typedef struct{
    char col1;
    int val1;
    char col2;
    int val2;
}tile_t;
typedef struct{
    int n_tess;
    tile_t *tess;
}tiles;

typedef struct {
    int fix;
    tile_t *ptess;
    int rot;
}cell;
typedef struct {
    int nr, nc;
    cell **celle;
}board;
typedef struct{
    int fix;
    int tess;
    int rot;
}cell_sol;

typedef struct{
    int punt;
    char color;
}punt_t;

void stampaScacchiera(board scacchiera,cell_sol *sol,tiles tessere);
void giocaR(int pos, tiles val, cell_sol *sol, int *mark,board scacc,cell_sol *best_sol, int *best_punt);
int calcolaPunt(int pos, cell_sol *sol, tiles val, int nr, int nc, punt_t *punt_righe, punt_t *punt_colonne, int punt_tot);

int main(int argc, char ** argv){
    // Dichiarazione e inizializzazione
    FILE *f_scacchiera,*f_tessere;
    int i,j,i_tess,i_rot, b_punt=0;
    int *mark;
    cell_sol *sol, *b_sol;
    tiles tessere;
    board scacchiera;

    // Lettura file TILES
    f_tessere = fopen(INPUT_TILES,"r");
    if(f_tessere == NULL){
        printf("Errore apertura file %s\n",INPUT_TILES);
        exit(-1);
    }
    fscanf(f_tessere,"%d\n", &tessere.n_tess);
    tessere.tess = (tile_t *) malloc(tessere.n_tess*sizeof(tile_t));
    mark = (int *)malloc(tessere.n_tess*sizeof(int));
    for(i=0; i<tessere.n_tess; i++){
        fscanf(f_tessere,"%c %d %c %d\n", &tessere.tess[i].col1, &tessere.tess[i].val1, &tessere.tess[i].col2,&tessere.tess[i].val2);
    }
    fclose(f_tessere);

    // Lettura file BOARD
    f_scacchiera = fopen(INPUT_BOARD,"r");
    if(f_scacchiera == NULL){
        printf("Errore apertura file %s\n",INPUT_BOARD);
        exit(-1);
    }
    fscanf(f_scacchiera,"%d %d\n", &scacchiera.nr, &scacchiera.nc);
    scacchiera.celle = (cell **) malloc(scacchiera.nr*sizeof(cell *));
    sol = (cell_sol *) malloc((scacchiera.nr*scacchiera.nc*sizeof(cell_sol)));
    b_sol = (cell_sol *) malloc((scacchiera.nr*scacchiera.nc*sizeof(cell_sol)));
    for(i=0; i< scacchiera.nr; i++){ // ogni riga
        scacchiera.celle[i] = (cell *) malloc(scacchiera.nc*sizeof(cell));
        for(j=0;j<scacchiera.nc;j++){
            fscanf(f_scacchiera,"%d/%d ", &i_tess, &scacchiera.celle[i][j].rot);
            if (i_tess>=0) {
                scacchiera.celle[i][j].ptess = &(tessere.tess[i_tess]);
                scacchiera.celle[i][j].fix = 1;
                sol[i*scacchiera.nr+j].tess = i_tess;
                sol[i*scacchiera.nr+j].rot = scacchiera.celle[i][j].rot;
                sol[i*scacchiera.nr+j].fix = 1;
                b_sol[i*scacchiera.nr+j].tess = i_tess;
                b_sol[i*scacchiera.nr+j].rot = scacchiera.celle[i][j].rot;
                b_sol[i*scacchiera.nr+j].fix = 1;
                mark[i_tess] = 1;
            }
            else {
                scacchiera.celle[i][j].ptess = NULL;
                scacchiera.celle[i][j].fix = 0;
                sol[i*scacchiera.nr+j].tess = -1;
                sol[i*scacchiera.nr+j].rot = -1;
                sol[i*scacchiera.nr+j].fix = 0;
                b_sol[i*scacchiera.nr+j].tess = -1;
                b_sol[i*scacchiera.nr+j].rot = -1;
                b_sol[i*scacchiera.nr+j].fix = 0;
            }
        }
    }
    fclose(f_scacchiera);

    printf("Soluzione: ");
    for(i=0;i<tessere.n_tess;i++) printf(" %d", sol[i].tess);
    printf("\n");
    giocaR(0,tessere,sol,mark,scacchiera,b_sol,&b_punt);
    printf("Migliore soluzione con punteggio massimo %d: \n",b_punt);
    stampaScacchiera(scacchiera,b_sol,tessere);

    free(mark);
    free(sol);
    free(b_sol);
    for (i = 0; i < scacchiera.nr; i++) {
        free(scacchiera.celle[i]);
    }
    free(scacchiera.celle);
    free(tessere.tess);

    return 0;
}

void gioca(board scacchiera) { // wrapper
    int i,j;

    for(i=0; i<scacchiera.nr; i++){
        for (j=0;j<scacchiera.nc; j++){
            if(scacchiera.celle[i][j].ptess==NULL){

            }
        }
    }
}

void giocaR(int pos, tiles val, cell_sol *sol, int*mark, board scacc, cell_sol *best_sol, int *best_punt){ // modello basato su disposizioni semplici
    int i,j,z,flag=0;
    int punteggio=0;
    punt_t p_righe[scacc.nr];
    punt_t p_colonne[scacc.nr];
    int p_tot=0;


    if(pos >= val.n_tess){
        for(i=0; i<scacc.nr;i++) {
            p_righe[i].punt = 0;
            p_righe[i].color = '\0';
        }
        for(i=0; i<scacc.nc;i++) {
            p_colonne[i].punt = 0;
            p_colonne[i].color = '\0';
        }


        /*
        for(i=0;i<scacc.nr;i++){
            for(j=0;j<scacc.nc;j++) {
                printf("%d ", sol[i*scacc.nr+j].tess);
            }
            printf("\n");
        }
        printf("\n");*/
        // stampaScacchiera(scacc,sol,val);
        /*printf("Soluzione: ");
        for(i=0;i<val.n_tess;i++) printf(" %d", sol[i].tess);
        printf("\n");*/
        punteggio = calcolaPunt(0,sol,val,scacc.nr,scacc.nc,p_righe,p_colonne,0);
        // printf("Punteggio: %d\n ",punteggio);
        /*printf("Punt_righe: ");
        for(i=0;i<scacc.nr;i++) printf("%c ",p_righe[i].color);
        for(i=0;i<scacc.nr;i++) printf("%d ",p_righe[i].punt);
        printf("\nPunt_colonne: ");
        for(i=0;i<scacc.nc;i++) printf("%c ",p_colonne[i].color);
        for(i=0;i<scacc.nc;i++) printf("%d ",p_colonne[i].punt);
        printf("\n");
        printf("Totale: %d\n ",punteggio);*/

        if(punteggio>(*best_punt)){ // condizione di ottimalità
            //stampaScacchiera(scacc,sol,val);
            // printf("Punteggio: %d\n ",punteggio);
            *best_punt = punteggio;
            for(i=0;i<val.n_tess;i++){
                best_sol[i].tess = sol[i].tess;
                best_sol[i].rot = sol[i].rot;
                best_sol[i].fix = sol[i].fix;
            }
        }

        return;

        /*printf("Soluzione: \n");
        // stampaScacchiera(scacc,sol,val);
        // aggiorno soluzione migliore

        for(i=0;i<scacc.nr;i++){
            for(j=0;j<scacc.nc;j++) {
                printf("%d ", sol[i*scacc.nr+j].tess);
            }
            printf("\n");
        }
        printf("\n");*/

    }

    /*debug stampa soluzione
    printf("Mark: ");
    for(i=0;i<val.n_tess;i++){
        printf("%d ",mark[i]);
    }
    printf("\n");
    printf("Soluzione parziale: ");
    for(i=0;i<pos;i++){
        printf("%d ",sol[i].tess);
    }
    printf("\n");
    */

    for(i=0; i<val.n_tess; i++){
        if(sol[pos].fix == 0){
            if(mark[i]==0){
                mark[i] =1;
                sol[pos].tess = i;
                sol[pos].rot = 0;
                giocaR(pos+1,val,sol,mark,scacc,best_sol,best_punt);
                sol[pos].rot = 1;
                giocaR(pos+1,val,sol,mark,scacc,best_sol,best_punt);
                mark[i]=0;
                sol[pos].tess = -1;
            }
        }else{
            giocaR(pos+1,val,sol,mark,scacc,best_sol,best_punt);
        }
    }
    return;
}

int calcolaPunt(int pos, cell_sol *sol, tiles val, int nr, int nc, punt_t *punt_righe, punt_t *punt_colonne, int punt_tot){
    int i,j,aaa;

    // condizione di terminazione
    if(pos==val.n_tess){
        punt_tot = 0;
        // Somma i punteggi delle righe e delle colonne
        for (i = 0; i < nr; i++) {
            if (punt_righe[i].color != 'F') { // Ignora righe fallite
                punt_tot += punt_righe[i].punt;
            }
        }
        for (j = 0; j < nc; j++) {
            if (punt_colonne[j].color != 'F') { // Ignora colonne fallite
                punt_tot += punt_colonne[j].punt;
            }
        }
        //for(i=0; i<nc; i++) punt_tot+=punt_colonne[i].punt;
        return punt_tot;
    }

    i = pos / nc;
    j = pos % nc;
    if(sol[pos].rot==1){
        if(punt_colonne[j].color==val.tess[sol[pos].tess].col1){
            punt_colonne[j].punt += val.tess[sol[pos].tess].val1;
        }else if(punt_colonne[j].color=='\0'){
            punt_colonne[j].color = val.tess[sol[pos].tess].col1;
            punt_colonne[j].punt += val.tess[sol[pos].tess].val1;
        }else{
            punt_colonne[j].punt = 0;
            punt_colonne[j].color = 'F';
        }
        //
        if(punt_righe[i].color==val.tess[sol[pos].tess].col2){
            punt_righe[i].punt += val.tess[sol[pos].tess].val2;
        }else if(punt_righe[i].color=='\0'){
            punt_righe[i].color += val.tess[sol[pos].tess].col2;
            punt_righe[i].punt += val.tess[sol[pos].tess].val2;
        }else{
            punt_righe[i].punt =0;
            punt_righe[i].color = 'F';
        }
        // se riga non ha stessi colori non ha punteggio!!!
        punt_tot = calcolaPunt(pos+1,sol,val,nr,nc,punt_righe,punt_colonne,punt_tot);
    }else{
        if(punt_colonne[j].color==val.tess[sol[pos].tess].col2){
            punt_colonne[j].punt += val.tess[sol[pos].tess].val2;
        }else if(punt_colonne[j].color=='\0'){
            punt_colonne[j].color = val.tess[sol[pos].tess].col2;
            punt_colonne[j].punt += val.tess[sol[pos].tess].val2;
        }else{
            punt_colonne[j].punt = 0;
            punt_colonne[j].color = 'F';
        }
        if(punt_righe[i].color==val.tess[sol[pos].tess].col1){
            punt_righe[i].punt += val.tess[sol[pos].tess].val1;
        }else if(punt_righe[i].color=='\0'){
            punt_righe[i].color = val.tess[sol[pos].tess].col1;
            punt_righe[i].punt += val.tess[sol[pos].tess].val1;
        }else{
            punt_righe[i].punt = 0;
            punt_righe[i].color = 'F';
        }
        punt_tot = calcolaPunt(pos+1,sol,val,nr,nc,punt_righe,punt_colonne,punt_tot);
    }
    return punt_tot;
    /*int i,j, punt_tot=0;
    punt_t punt_righe[nr];
    punt_t punt_colonne[nc];
    for(i=0;i<nr;i++) punt_righe[i].punt = 0; punt_righe[i].color = 0;
    for(i=0;i<nc;i++) punt_colonne[i].punt = 0; punt_colonne[i].color = 0;

    for(i=0;i<nr;i++){
        for(j=0; j<nc; j++){
            if(punt_righe[i].color == 0 && punt_colonne[j].color == 0){ // setto righa i e colonna i con colore corrispondente e incr. punteggio
                if (sol[i*nr+j].rot == 1){
                    punt_colonne[j].punt = val.tess[sol[i*nr+j].tess].val1;
                    punt_colonne[j].color = val.tess[sol[i*nr+j].tess].col1;

                    punt_righe[i].punt = val.tess[sol[i*nr+j].tess].val2;
                    punt_righe[i].color = val.tess[sol[i*nr+j].tess].col2;
                }else{
                    punt_colonne[j].punt = val.tess[sol[i*nr+j].tess].val2;
                    punt_colonne[j].color = val.tess[sol[i*nr+j].tess].col2;

                    punt_righe[i].punt = val.tess[sol[i*nr+j].tess].val1;
                    punt_righe[i].color = val.tess[sol[i*nr+j].tess].col1;
                }
            }else{
                if (sol[i*nr+j].rot == 0){
                    if(punt_righe[i].color == val.tess[sol[i*nr+j].tess].col2 && punt_colonne[j].color == val.tess[sol[i*nr+j].tess].col1){
                        punt_colonne[j].punt +=  val.tess[sol[i*nr+j].tess].val1;
                        punt_righe[i].punt +=  val.tess[sol[i*nr+j].tess].val2;
                    }else{
                        return 0;
                    }
                }else{
                    if(punt_righe[i].color == val.tess[sol[i*nr+j].tess].col1 && punt_colonne[j].color == val.tess[sol[i*nr+j].tess].col2){
                        punt_colonne[j].punt +=  val.tess[sol[i*nr+j].tess].val2;
                        punt_righe[i].punt +=  val.tess[sol[i*nr+j].tess].val1;
                    }else{
                        return 0;
                    }
                }
            }

        }

    }
    for(i=0; i<nr; i++) punt_tot+=punt_righe[i].punt;
    for(i=0; i<nc; i++) punt_tot+=punt_colonne[i].punt;

    return punt_tot;
    */

}
void stampaScacchiera(board scacchiera, cell_sol *sol, tiles tessere){
    int i, j,kn, z;


    char* cella_orizz[11] = {
            "      +----+      ",
            "      |  ",
            " |      ",
            " +----+----+----+ ",
            " |  " ,
            "        ",
            " | ",
            " +----+----+----+ ",
            "      | ",
            " |      ",
            "      +----+      ",
    };

    char* cella_vert[11] = {
            "      +----+      ",
            "      |  "," |      ",
            " +----+    +----+ ",
            " |  "," |    | "," | ",
            " +----+    +----+ ",
            "      | "," |      ",
            "      +----+      ",
    };
    char* cella_vuota[7] = {
            " +              + ",
            "                  ",
            "                  ",
            "                  ",
            "                  ",
            "                  ",
            " +              + ",
    };

    int *ko = calloc(scacchiera.nc,sizeof(int));
    int *kv = calloc(scacchiera.nc,sizeof(int));

/*    for(i=0; i<11;i++)
        printf("%s\n",cella_orizz[i]);*/

    for(i=0; i<scacchiera.nr;i++){
        for(z=0; z<scacchiera.nc; z++) {
            ko[z] = 0;
            kv[z] = 0;
        }
        for(kn=0 ;kn<7; kn++) {
            for (j = 0; j < scacchiera.nc; j++) {
                if (scacchiera.celle[i][j].fix == 1) { // celle iniziali di gioco
                    if (scacchiera.celle[i][j].rot == 1) {
                        //printf("kv[j]: %d \n",kv[j]);
                        if (kv[j] == 1) {
                            //printf("%c\n",scacchiera.celle[i][j].ptess->col1);
                            printf("%s%c%s", cella_vert[kv[j]++], scacchiera.celle[i][j].ptess->col1,cella_vert[kv[j]++]);
                        } else if (kv[j] == 8) {
                            printf("%s%02d%s", cella_vert[kv[j]++], scacchiera.celle[i][j].ptess->val1,cella_vert[kv[j]++]);
                        } else if (kv[j] == 4) {
                            printf("%s%c%s%02d%s", cella_vert[kv[j]++], scacchiera.celle[i][j].ptess->col2,cella_vert[kv[j]++], scacchiera.celle[i][j].ptess->val2, cella_vert[kv[j]++]);
                        } else {
                            printf("%s", cella_vert[kv[j]++]);
                        }
                    }
                    else if (scacchiera.celle[i][j].rot == 0) {
                        // printf("ko[j]: %d \n",ko[j]);
                        if (ko[j] == 1) {
                            printf("%s%c%s", cella_orizz[ko[j]++], (char)scacchiera.celle[i][j].ptess->col2, cella_orizz[ko[j]++]);
                        } else if (ko[j] == 8) {
                            printf("%s%02d%s", cella_orizz[ko[j]++], scacchiera.celle[i][j].ptess->val2,
                                   cella_orizz[ko[j]++]);
                        } else if (ko[j] == 4) {
                            printf("%s%c%s%02d%s", cella_orizz[ko[j]++], (char)scacchiera.celle[i][j].ptess->col1,cella_orizz[ko[j]++], scacchiera.celle[i][j].ptess->val1, cella_orizz[ko[j]++]);
                        } else {
                            //puts(cella_orizz[ko[j]]);
                            printf("%s", cella_orizz[ko[j]++]);
                        }
                    }
                } else if (sol[i * scacchiera.nr + j].tess >= 0) { // cella soluzione
                    if (sol[i * scacchiera.nr + j].rot == 1) {
                        if (kv[j] == 1) {
                            printf("%s%c%s", cella_vert[kv[j]++],(char)tessere.tess[sol[i * scacchiera.nr + j].tess].col1, cella_vert[kv[j]++]);
                        } else if (kv[j] == 8) {
                            printf("%s%02d%s", cella_vert[kv[j]++],tessere.tess[sol[i * scacchiera.nr + j].tess].val1, cella_vert[kv[j]++]);
                        } else if (kv[j] == 4) {
                            printf("%s%c%s%02d%s", cella_vert[kv[j]++],(char)tessere.tess[sol[i * scacchiera.nr + j].tess].col2, cella_vert[kv[j]++],tessere.tess[sol[i * scacchiera.nr + j].tess].val2, cella_vert[kv[j]++]);
                        } else {
                            printf("%s", cella_vert[kv[j]++]);
                        }
                    }
                    else if (sol[i * scacchiera.nr + j].rot == 0) {
                        if (ko[j] == 1) {
                            printf("%s%c%s", cella_orizz[ko[j]++],tessere.tess[sol[i * scacchiera.nr + j].tess].col2, cella_orizz[ko[j]++]);
                        } else if (ko[j] == 8) {
                            printf("%s%02d%s", cella_orizz[ko[j]++],tessere.tess[sol[i * scacchiera.nr + j].tess].val2, cella_orizz[ko[j]++]);
                        } else if (ko[j] == 4) {
                            printf("%s%c%s%02d%s", cella_orizz[ko[j]++],tessere.tess[sol[i * scacchiera.nr + j].tess].col1, cella_orizz[ko[j]++],tessere.tess[sol[i * scacchiera.nr + j].tess].val1, cella_orizz[ko[j]++]);
                        } else {
                            printf("%s", cella_orizz[ko[j]++]);
                        }
                    }
                }else { // cella vuota
                    printf("%s", cella_vuota[kn]);
                }
            }
            printf("\n");
        }
    }
}