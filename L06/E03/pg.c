//
// Created by Diego Campanale on 22/11/24.
//

#include <stdlib.h>
#include "pg.h"

int leggiPG(FILE *fin, pg_t *pg){
    return fscanf(fin, "%s %s %s %d %d %d %d %d %d\n",pg->codice, pg->nome, pg->classe, &pg->stat.hp,&pg->stat.mp, &pg->stat.atk,&pg->stat.atk, &pg->stat.mag, &pg->stat.spr);
}

void stampaPG(FILE *fout, pg_t *pg){
    fprintf(fout,"%s %s %s %d %d %d %d %d %d\n",pg->codice, pg->nome, pg->classe, pg->stat.hp,pg->stat.mp, pg->stat.atk, pg->stat.def, pg->stat.mag, pg->stat.spr);
}

void leggiFilePG(char *nomefile, tabPg_t *tabPg){
    FILE *fp = fopen(nomefile, "r");
    if(fp==NULL){ printf("Errore apertura %s!\n",nomefile);exit(-1);}
    pg_t *Ppg =malloc(sizeof(pg_t));
    while (leggiPG(fp,Ppg)!=EOF){
        stampaPG(stdout,Ppg);
        // inserimento personaggio in lista
    }


    fclose(fp);


}