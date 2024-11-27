#include <stdlib.h>
#include <string.h>
#include "inv.h"
#define MAXL 51


typedef struct modStat_s{
        int hp,mp,atk,def,mag,spr;
}modStat_t;

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
tabInv_t *allocaInv(int max){
    tabInv_t *inv = malloc(sizeof(tabInv_t));
    inv->maxInv = max;
    inv->nInv = 0;
    inv->vettInv = malloc(max*sizeof(inv_t));
    return inv;
}
tabInv_t *leggiFileInv(char *nomefile){
    tabInv_t *tabInv;
    int i, nOgg;
    char nome[MAXL], tipo[MAXL];

    FILE *f = fopen(nomefile,"r");
    if (f==NULL) return NULL;

    fscanf(f,"%d",&nOgg);
    tabInv = allocaInv(nOgg);
    for(i=0; i<nOgg;i++){
        leggiOggetto(f,nome,tipo,&tabInv->vettInv[i].modStat);
        tabInv->vettInv[i].nome = strdup(nome);
        tabInv->vettInv[i].tipo = strdup(tipo);
    }
    tabInv->nInv = nOgg;
    fclose(f);
    return tabInv;
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
    fprintf(fout, "\tSPR: %d\n", ogg->modStat.spr);
}
void liberaInv(tabInv_t *tabInv){
    int i;
    for(i=0; i<tabInv->nInv; i++){
        free(tabInv->vettInv[i].nome);
        free(tabInv->vettInv[i].tipo);
    }
    free(tabInv->vettInv);
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