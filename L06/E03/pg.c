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

typedef struct stat_s{
    unsigned int hp, mp,atk,def,mag,spr;
}stat_t;

struct pg_s{
    char *codice;
    char *nome;
    char *classe;
    tabEquip_t *equip;
    stat_t stat;
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
    else fprintf(fout,"\tMP: %d",pg->stat.mp);
    if(pg->stat.atk<0) fprintf(fout,"\tATK: %d",0);
    else fprintf(fout,"\tATK: %d",pg->stat.atk);
    if(pg->stat.def<0) fprintf(fout,"\tDEF: %d",0);
    else fprintf(fout,"\tDEF: %d",pg->stat.def);
    if(pg->stat.mag<0) fprintf(fout,"\tMAG: %d",0);
    else fprintf(fout,"\tMAG: %d",pg->stat.mag);
    if(pg->stat.spr<0) fprintf(fout,"\tSPR: %d",0);
    else fprintf(fout,"\tSPR: %d\n",pg->stat.spr);
    if (pg->equip!=NULL && pg->equip->inUso>0){
        fprintf(fout,"Equipaggiamento:\n");
        stampaEquip(fout,pg->equip);
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

static void liberaEquip(tabEquip_t *tabEquip){
    free(tabEquip->vettEq);
    free(tabEquip);
}

static linkPg newNodePG(pg_t val, linkPg next){
    linkPg x = malloc(sizeof(nodePg_t));
    if(x==NULL)
        return NULL;
    x->pg = val;
    x->next = next;
    return x;
}

static int listInsPG(tabPg_t *tabPg, pg_t pg){
    if(tabPg->tailPg == NULL){
        tabPg->headPg = tabPg->tailPg = newNodePG(pg,NULL);
        tabPg->nPg++;
    }else{
        tabPg->tailPg->next = newNodePG(pg,NULL);
        tabPg->nPg++;
    }
    return 1;
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
int aggiungiPG(tabPg_t *tabPg, char *codice, char *nome, char *classe, int hp,int mp,int atk,int def,int mag,int spr){
    pg_t *pg = malloc(sizeof(pg_t));

    pg->codice = strdup(codice);
    pg->nome = strdup(nome);
    pg->classe = strdup(classe);
    pg->stat.hp = hp;
    pg->stat.mp = mp;
    pg->stat.atk = atk;
    pg->stat.def = def;
    pg->stat.mag = mag;
    pg->stat.spr = spr;
    int r = listInsPG(tabPg,*pg);
    free(pg);
    return r;
}
static void printListR(FILE* fout,linkPg h){
    if(h==NULL)
        return;
    stampaPG(fout,&h->pg);
    printListR(fout,h->next);
}

void stampaListPG(FILE *fout,tabPg_t *tabPg){
    printListR(fout,tabPg->headPg);
}

int numPG(tabPg_t *tabPg){
    return tabPg->nPg;
}

static pg_t PGsetVoid(){
    pg_t pg;
    pg.nome = NULL;
    pg.codice = NULL;
    pg.classe = NULL;
    pg.stat.hp = pg.stat.mp = pg.stat.atk = pg.stat.def = pg.stat.mag = pg.stat.spr = 0;
    pg.equip = NULL;
    return pg;
}

int isVoidPg(pg_t *pg){
    return (pg->codice==NULL);
}

pg_t *cercaPG(tabPg_t *tabPg, char *codice){
    linkPg x;
    for(x=tabPg->headPg; x!= NULL ; x = x->next){
        if(strcmp(codice,x->pg.codice)==0){
            return &x->pg;
        }
    }
    return NULL;
}

static pg_t listExtrKeyP(linkPg *h,char *key){
    linkPg *xp, t;
    pg_t pg; pg = PGsetVoid();
    for(xp=h; (*xp)!= NULL ; xp = &((*xp)->next) ){
        if(strcmp(key,(*xp)->pg.codice)==0){
            t = *xp;
            *xp = (*xp)->next;
            pg = t->pg;
            free(t);
            break;
        }
    }
    return pg;
}

pg_t *rimuoviPG(tabPg_t *tabPg, char *codice){
    pg_t extract;
    extract = listExtrKeyP(&tabPg->headPg,codice);

    if(isVoidPg(&extract)){
        return 0;
        printf("Nessun personaggio rimosso\n");
    }else{

        printf("Personaggio rimosso:\n");
        stampaPG(stdout,&extract);
    }
}

void updateStat(struct stat_s *stat, inv_t *ogg){
    stat->hp+= getHP(ogg);
    stat->mp+= getMP(ogg);
    stat->atk+= getATK(ogg);
    stat->def+= getDEF(ogg);
    stat->mag+= getMAG(ogg);
    stat->spr+= getSPR(ogg);
}

void aggiungiEquip(pg_t *pg, inv_t *ogg){
    int i = pg->equip->inUso;
    if(i<MAXE){
        pg->equip->vettEq[i] = ogg;
        updateStat(&pg->stat,ogg);
        pg->equip->inUso++;
    } else{
        printf("Equipaggiamento al completo! Rimuovi un oggetto prima.\n");
    }
}

inv_t *rimuoviEquip(pg_t *pg, int e){
    inv_t *t = pg->equip->vettEq[e];
    pg->equip->vettEq[e] = NULL;
    return t;
}

static void liberaPG(pg_t *pg){
    free(pg->codice);
    free(pg->nome);
    free(pg->classe);
    if(pg->equip!=NULL)
        liberaEquip(pg->equip);
    free(pg);
}

void liberaListPG(tabPg_t *tabPg){
    linkPg p, q;
    for(p=tabPg->headPg; p!=NULL; p=q){
        q = p->next;
        liberaPG(&(p->pg));
    }
    free(tabPg);
}
