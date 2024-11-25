//
// Created by Diego Campanale on 22/11/24.
//

#include <stdlib.h>
#include "inv.h"

void leggiFileInv(char *nomefile, tabInv_t *tabInv){
    FILE *fp = fopen(nomefile, "r");
    if(fp==NULL){ printf("Errore apertura %s!\n",nomefile);exit(-1);}

    fscanf(fp, "%d\n", tabInv->nInv);

    // rivedi
    inv_t *pInv =malloc(sizeof(inv_t));
    while (leggiOggetto(fp,pInv)!=EOF){
        stampaOggetto(stdout,pInv);
        // inserimento personaggio in lista
    }
}


int leggiOggetto(FILE *fin, inv_t *ogg){
    return fscanf(fin, "%s %s %d %d %d %d %d %d\n", ogg->nome, ogg->tipo, &ogg->modStat.hp, &ogg->modStat.mp, &ogg->modStat.atk, &ogg->modStat.def, &ogg->modStat.mag, &ogg->modStat.spr);
}

void stampaOggetto(FILE *fout, inv_t *ogg){
    fprintf(fout, "%s %s %d %d %d %d %d %d\n", ogg->nome, ogg->tipo, ogg->modStat.hp, ogg->modStat.mp, ogg->modStat.atk, ogg->modStat.def, ogg->modStat.mag, ogg->modStat.spr);
}