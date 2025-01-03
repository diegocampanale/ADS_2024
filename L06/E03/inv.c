#include <stdlib.h>
#include <string.h>
#include "inv.h"
#define MAXL 51


typedef struct modStat_s{
    int hp,mp,atk,def,mag,spr;
};

struct inv_s{
    char *nome;
    char *tipo;
    modStat_t modStat;
};

struct tabInv_s{
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

static int leggiOggetto(FILE *fin, char *nome, char *tipo, modStat_t *stat);

int getHP(inv_t *ogg){
    return ogg->modStat.hp;
}
int getMP(inv_t *ogg){
    return ogg->modStat.mp;
}
int getATK(inv_t *ogg){
    return ogg->modStat.atk;
}
int getDEF(inv_t *ogg){
    return ogg->modStat.def;
}
int getMAG(inv_t *ogg){
    return ogg->modStat.mag;
}
int getSPR(inv_t *ogg){
    return ogg->modStat.spr;
}

tabInv_t *allocaInv(int max){
    tabInv_t *inv = malloc(sizeof(tabInv_t));
    inv->maxInv = max;
    inv->nInv = 0;
    inv->vettInv = malloc(max*sizeof(inv_t));
    return inv;
}
int leggiFileInv(tabInv_t **pTabInv, char *nomefile){
    FILE *f = fopen(nomefile,"r");
    if (f==NULL) return 0;

    int i, nOgg;
    char nome[MAXL], tipo[MAXL];

    fscanf(f,"%d",&nOgg);

    if(*pTabInv == NULL){
        *pTabInv = allocaInv(nOgg);
    }
    for(i=0; i<nOgg;i++){
        leggiOggetto(f,nome,tipo,&(*pTabInv)->vettInv[i].modStat);
        (*pTabInv)->vettInv[i].nome = strdup(nome);
        (*pTabInv)->vettInv[i].tipo = strdup(tipo);
    }
    (*pTabInv)->nInv = nOgg;
    fclose(f);
    return nOgg;
}
static int leggiOggetto(FILE *fin, char *nome, char *tipo, modStat_t *stat){
    return fscanf(fin, "%s %s %d %d %d %d %d %d\n",
                  nome, tipo, &stat->hp, &stat->mp, &stat->atk, &stat->def, &stat->mag, &stat->spr);
}
void stampaOggetto(FILE *fout, inv_t *ogg){
    fprintf(fout, "nome: %s", ogg->nome);
    fprintf(fout, "\ttipo: %s", ogg->tipo);
    fprintf(fout, "\tHP: %d", ogg->modStat.hp);
    fprintf(fout, "\tMP: %d", ogg->modStat.mp);
    fprintf(fout, "\tATK: %d", ogg->modStat.atk);
    fprintf(fout, "\tDEF: %d", ogg->modStat.def);
    fprintf(fout, "\tMAG: %d", ogg->modStat.mag);
    fprintf(fout, "\tSPR: %d", ogg->modStat.spr);
}
void liberaInv(tabInv_t *tabInv){
    int i;
    if(tabInv != NULL){
        for(i=0; i<(tabInv->nInv); i++){
            free(tabInv->vettInv[i].nome);
            free(tabInv->vettInv[i].tipo);
        }
        free(tabInv->vettInv);
    }
    free(tabInv);
}
inv_t *cercaOggetto(tabInv_t *tabInv, char *nome){
    int i;
    for(i=0;i<tabInv->nInv;i++){
        if(strcmp(tabInv->vettInv[i].nome,nome)==0){
            return &tabInv->vettInv[i];
        }
    }
    return NULL;
}
int numINV(tabInv_t *tabInv){
    return tabInv->nInv;
}
void stampaOggetti(FILE *fout, tabInv_t *tabInv){
    int i;
    for(i=0;i<tabInv->nInv;i++){
        printf("%d - ",i);
        stampaOggetto(fout,&tabInv->vettInv[i]);
        printf("\n");
    }
}

char *getNameINV(inv_t *ogg){
    return ogg->nome;
}