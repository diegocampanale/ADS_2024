#include <stdlib.h>
#include <string.h>
#include "pg.h"
#include "inv.h"
#define MAXS 51
#define MAXC 7
#define MAXE 8

struct tabEquip_s{
    int inUso;
    inv_t **vettEq;
};

struct pg_s{
    char *codice;
    char *nome;
    char *classe;
    tabEquip_t *equip;
    struct stat_s{
        unsigned int hp, mp,atk,def,mag,spr;
    }stat;
};

struct nodePg_s{
    pg_t pg;
    linkPg next;
};
struct tabPg_s{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
};

static void stampaEquip(FILE *f,tabEquip_t *equip){
    int i;
    for(i=0;i<equip->inUso;i++){
        fprintf(f,"%d - ",i);
        stampaOggetto(f,equip->vettEq[i]);
        printf("\n");
    }
}

static int leggiPG(FILE *fin, char *codice, char *nome, char *classe, struct stat_s *stat){
    return fscanf(fin, "%s %s %s %d %d %d %d %d %d\n",codice, nome, classe, &stat->hp,&stat->mp, &stat->atk,&stat->def, &stat->mag, &stat->spr);
}

void stampaPG(FILE *fout, pg_t *pg){
    //fprintf(fout,"%s %s %s %d %d %d %d %d %d\n",pg->codice, pg->nome, pg->classe, pg->stat.hp,pg->stat.mp, pg->stat.atk, pg->stat.def, pg->stat.mag, pg->stat.spr);
    fprintf(fout,"CODICE: %s\n",pg->codice);
    fprintf(fout,"NOME: %s\n",pg->nome);
    fprintf(fout,"CLASSE: %s\n",pg->classe);
    fprintf(fout,"Statistiche:\n");
    if(pg->stat.hp<0) fprintf(fout,"\tHP: %d",0);
    else fprintf(fout,"\tHP: %d",pg->stat.hp);
    if(pg->stat.mp<0) fprintf(fout,"\tMP: %d",0);
    else fprintf(fout,"\tMP: %d",pg->stat.hp);
    if(pg->stat.atk<0) fprintf(fout,"\tATK: %d",0);
    else fprintf(fout,"\tATK: %d",pg->stat.hp);
    if(pg->stat.def<0) fprintf(fout,"\tDEF: %d",0);
    else fprintf(fout,"\tDEF: %d",pg->stat.hp);
    if(pg->stat.mag<0) fprintf(fout,"\tMAG: %d",0);
    else fprintf(fout,"\tMAG: %d",pg->stat.hp);
    if(pg->stat.spr<0) fprintf(fout,"\tSPR: %d",0);
    else fprintf(fout,"\tSPR: %d\n",pg->stat.hp);
    if (pg->equip->inUso>0){
        fprintf(fout,"Equipaggiamento:\n");
        stampaEquip(fout,&pg->equip);
    }
    printf("\n");
}

tabPg_t *allocaPG(){
    tabPg_t *tpg = malloc(sizeof(tabPg_t));
    tpg->headPg=NULL;
    tpg->tailPg=NULL;
    tpg->nPg=0;
    return tpg;
}
static tabEquip_t *allocaEquip(){
    tabEquip_t *tabEquip = malloc(sizeof(tabEquip_t));
    tabEquip->inUso=0;
    tabEquip->vettEq= malloc(MAXE*sizeof(inv_t *));
    return tabEquip;
}

static linkPg newNodePG(pg_t val, linkPg next){
    linkPg x = malloc(sizeof(nodePg_t));
    if(x==NULL)
        return NULL;
    x->pg = val;
    x->next = next;
    return x;
}

static void listInsPG(tabPg_t *tabPg, pg_t pg){
    if(tabPg->headPg == NULL){
        tabPg->headPg = newNodePG(pg,tabPg->headPg);
        tabPg->tailPg = tabPg->headPg;
        tabPg->nPg++;
    }else{
        tabPg->headPg = newNodePG(pg,tabPg->headPg);
        tabPg->nPg++;
    }
}

tabPg_t *leggiFilePG(char *nomefile){
    tabPg_t *tabPg;
    int i;
    char codice[MAXC], nome[MAXS], classe[MAXS];
    pg_t *pg = malloc(sizeof(pg_t));

    FILE *fp = fopen(nomefile, "r");
    if(fp==NULL) return NULL;

    tabPg = allocaPG();

    while (leggiPG(fp,codice,nome,classe,&pg->stat)!=EOF){
        pg->codice = strdup(codice);
        pg->nome = strdup(nome);
        pg->classe = strdup(classe);
        pg->equip = allocaEquip();
        listInsPG(tabPg,*pg);
    }

    fclose(fp);
    return tabPg;
}



