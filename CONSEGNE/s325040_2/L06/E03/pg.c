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


void stampaEquip(FILE *f,tabEquip_t *equip){
    int i;
    for(i=0;i<equip->inUso;i++){
        fprintf(f,"%d - ",i);
        stampaOggetto(f,equip->vettEq[i]);
        printf("\n");
    }
}
static int leggiPG(FILE *fin, char *codice, char *nome, char *classe, int *hp, int *mp, int *atk, int *def, int *mag, int *spr){
    return fscanf(fin, "%s %s %s %d %d %d %d %d %d\n",codice, nome, classe, hp, mp, atk, def, mag, spr);
}
static void liberaEquip(tabEquip_t *tabEquip){
    if(tabEquip==NULL) return;
    free(tabEquip->vettEq);
    free(tabEquip);
}
void stampaPG(FILE *fout, pg_t *pg){
    printf("\n");
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

    fprintf(fout,"n. oggetti: %d\n", pg->equip->inUso);
    if (pg->equip->vettEq!=NULL && pg->equip->inUso>0){
        fprintf(fout,"Equipaggiamento:\n");
        stampaEquip(fout,pg->equip);
    }
    printf("\n");
}
tabPg_t *allocaTabPG(){
    tabPg_t *tpg = malloc(sizeof(tabPg_t));
    tpg->headPg=NULL;
    tpg->tailPg=NULL;
    tpg->nPg=0;
    return tpg;
}

static tabEquip_t *allocaEquip(){
    tabEquip_t *tabEquip = malloc(sizeof(tabEquip_t));
    if (tabEquip == NULL) return NULL;
    tabEquip->inUso=0;

    tabEquip->vettEq= malloc(MAXE*sizeof(inv_t *));
    if (tabEquip->vettEq == NULL) {
        fprintf(stderr, "Errore: impossibile allocare vettEq.\n");
        free(tabEquip);  // Libera tabEquip in caso di errore
        return NULL;
    }
    for (int i = 0; i < MAXE; i++) {
        tabEquip->vettEq[i] = NULL;
    }
    return tabEquip;
}
/*static void initPG(pg_t *pg) {
    if (pg == NULL) return;  // Verifica che il puntatore sia valido

    // Allocazione della memoria
    pg->nome = malloc(MAXS);
    pg->codice = malloc(MAXC);
    pg->classe = malloc(MAXS);
    pg->equip = allocaEquip();

    // Verifica che l'allocazione sia avvenuta con successo
    if (pg->nome == NULL || pg->codice == NULL || pg->classe == NULL || pg->equip == NULL) {
        liberaPG(pg);  // Libera tutte le risorse allocate finora
        return;
    }

    // Inizializza i campi (se necessario, per debug o utilizzo futuro)
    pg->nome[0] = '\0';
    pg->codice[0] = '\0';
    pg->classe[0] = '\0';
    pg->equip->inUso = 0;
}*/
static void initPG(pg_t *pg) {
    if (pg == NULL) return;

    if (pg->nome != NULL) free(pg->nome);
    if (pg->codice != NULL) free(pg->codice);
    if (pg->classe != NULL) free(pg->classe);
    if (pg->equip != NULL) liberaEquip(pg->equip);

    pg->nome = malloc(MAXS);
    pg->codice = malloc(MAXC);
    pg->classe = malloc(MAXS);
    pg->equip = allocaEquip();
}

/*void PGcpy(pg_t *dest, pg_t *src){
    strcpy(dest->codice,src->codice);
    strcpy(dest->nome,src->nome);
    strcpy(dest->classe,src->classe);
    dest->stat.hp = src->stat.hp;
    dest->stat.mp = src->stat.mp;
    dest->stat.atk = src->stat.atk;
    dest->stat.def = src->stat.def;
    dest->stat.mag= src->stat.mag;
    dest->stat.spr = src->stat.spr;
}*/

void PGcpy(pg_t *dest, pg_t *src) {
    if (dest == NULL || src == NULL) {
        fprintf(stderr, "Errore: puntatore nullo passato a PGcpy.\n");
        return;
    }

    // Libera i campi esistenti di dest per evitare memory leaks
    if (dest->codice != NULL) free(dest->codice);
    if (dest->nome != NULL) free(dest->nome);
    if (dest->classe != NULL) free(dest->classe);
    if (dest->equip != NULL) liberaEquip(dest->equip);

    // Duplica i valori da src a dest
    dest->codice = strdup(src->codice);
    dest->nome = strdup(src->nome);
    dest->classe = strdup(src->classe);

    // Verifica che la duplicazione sia avvenuta con successo
    if (dest->codice == NULL || dest->nome == NULL || dest->classe == NULL) {
        fprintf(stderr, "Errore: duplicazione memoria fallita in PGcpy.\n");
        return;
    }

    // Copia le statistiche
    dest->stat.hp = src->stat.hp;
    dest->stat.mp = src->stat.mp;
    dest->stat.atk = src->stat.atk;
    dest->stat.def = src->stat.def;
    dest->stat.mag = src->stat.mag;
    dest->stat.spr = src->stat.spr;

    dest->equip->inUso = src->equip->inUso;
    // copia l'equipaggiamento
    if(src->equip->inUso>0){
        int i;
        for(i=0;i>src->equip->inUso;i++){
            dest->equip->vettEq[i] = src->equip->vettEq[i];
        }
    }
}


/*static linkPg newNodePG(pg_t val, linkPg next){
    linkPg x = malloc(sizeof(nodePg_t));
    initPG(&x->pg);
    if(x==NULL)
        return NULL;
    PGcpy(&x->pg,&val);
    x->next = next;
    return x;
}*/
static linkPg newNodePG(pg_t val, linkPg next) {
    linkPg x = malloc(sizeof(nodePg_t));
    if (x == NULL) {
        return NULL;
    }
    x->pg.codice = strdup(val.codice);
    x->pg.nome = strdup(val.nome);
    x->pg.classe = strdup(val.classe);
    x->pg.stat = val.stat;
    x->pg.equip = allocaEquip(); // Assumi che l'equip sia vuoto
    x->next = next;
    return x;
}
static void listInsPG(tabPg_t **tabPg, pg_t *pg){
    if((*tabPg)->headPg == NULL){
        (*tabPg)->headPg = (*tabPg)->tailPg = newNodePG(*pg,NULL);
        (*tabPg)->nPg++;
    }else{
        (*tabPg)->tailPg->next = newNodePG(*pg,NULL);
        (*tabPg)->tailPg = (*tabPg)->tailPg->next;
        (*tabPg)->nPg++;
    }

}
/*int leggiFilePG(tabPg_t **pTabPg,char *nomefile){
    FILE *fp = fopen(nomefile, "r");
    if(fp==NULL) return 0;


    int i, cnt=0;
    char codice[MAXC], nome[MAXS], classe[MAXS];
    if(*pTabPg == NULL){
        *pTabPg = allocaTabPG();
    }
    pg_t *pg = allocaPG(); // struct personaggio temporanea

    while (leggiPG(fp,codice,nome,classe,&pg->stat)!=EOF){
        pg->codice = strdup(codice);
        pg->nome = strdup(nome);
        pg->classe = strdup(classe);
        cnt += aggiungiPG(pTabPg,pg);
    }
    liberaPG(pg); // libera struct personaggio temporanea
    fclose(fp);
    return cnt;
}*/
int leggiFilePG(tabPg_t **pTabPg, char *nomefile) {
    FILE *fp = fopen(nomefile, "r");
    if (fp == NULL) {
        return 0;
    }

    int cnt = 0;
    char codice[MAXC], nome[MAXS], classe[MAXS];
    int hp,mp,atk,def,mag,spr;
    if (*pTabPg == NULL) {
        *pTabPg = allocaTabPG();
    }

    while (leggiPG(fp, codice, nome, classe, &hp,&mp,&atk,&def,&mag,&spr) != EOF) {
        pg_t *pg = allocaPG();
        setCodicePG(pg, codice);
        setNomePG(pg, nome);
        setClassePG(pg, classe);
        setStatPG(pg,hp,mp,atk,def,mag,spr);
        cnt += aggiungiPG(pTabPg, pg);
        liberaPG(pg);
    }

    fclose(fp);
    return cnt;
}
/*int aggiungiPG(tabPg_t **tabPg, pg_t *pg){
    pg_t *pgE = NULL;
    if((*tabPg)->headPg!=NULL){
        pgE = cercaPG(*tabPg,pg->codice); // restit puntatore a struct pg del nodo se esiste
    }
    if(pgE==NULL) {
        listInsPG(tabPg, pg);
        return 1;
    }
    // aggiorna personaggio
    PGcpy(pgE,pg);

    return 0;
}*/
int aggiungiPG(tabPg_t **tabPg, pg_t *pg) {
    if (pg == NULL || pg->codice == NULL) {
        return -1;
    }
    if (*tabPg == NULL) {
        *tabPg = allocaTabPG();
    }
    pg_t *pgE = cercaPG(*tabPg, pg->codice);
    if (pgE == NULL) {
        listInsPG(tabPg, pg);
        return 1;
    }
    PGcpy(pgE, pg); // Aggiorna i dati del personaggio
    printf("Personaggio modificato:\n");
    stampaPG(stdout,pgE);

    return 0;
}
static void printListR(FILE* fout,linkPg h){
    if(h==NULL)
        return;
    stampaPG(fout,&h->pg);
    printListR(fout,h->next);
}
void stampaListPG(FILE *fout,tabPg_t *tabPg){
    printf("\n");
    if(tabPg!=NULL)
        printListR(fout,tabPg->headPg);
}
int numPG(tabPg_t *tabPg){
    return tabPg->nPg;
}

int isVoidPg(pg_t *pg){
    return !strcmp(pg->codice,"");
}
pg_t *cercaPG(tabPg_t *tabPg, char *codice){
    if(tabPg->headPg==NULL) return NULL;
    linkPg x; // = malloc(sizeof(linkPg));
    pg_t *t;
    // initPG(&(x->pg));
    x->next = NULL;
    for(x=tabPg->headPg; x!= NULL ; x = x->next){
        if(strcmp(x->pg.codice,codice)==0){
            return &x->pg;
        }
    }
    return NULL;
}
pg_t **cercaPgPunt(tabPg_t *tabPg, char *codice){
    pg_t **pPg = malloc(sizeof(pg_t *));
    *pPg = cercaPG(tabPg,codice);
    return pPg;
}
static pg_t listExtrKeyP(linkPg *h,linkPg *t,char *key){

    // initPG(&(*xp)->pg);
    linkPg *xp; //  = malloc(sizeof(linkPg));
    linkPg *pp; // = malloc(sizeof(linkPg)
    linkPg tmp; // = malloc(sizeof(nodePg_t));

    //*pp = NULL;
    // (*xp)->next = NULL;
    pg_t *pg = allocaPG();
    if(h==NULL) return *pg;

    for(xp=h, pp=NULL; (*xp)!= NULL ; pp = xp, xp = &((*xp)->next) ){
        if(strcmp(key,(*xp)->pg.codice)==0){
            tmp = *xp;

            if(tmp->next==NULL && (*h)->next != NULL ){ // se l'elemento da estrarre è l'ultimo , modifico tail
                *t = *pp;
            }
            *xp = (*xp)->next;

            PGcpy(pg,&tmp->pg);
            liberaPG(&tmp->pg);
            break;
        }
    }
    free(tmp);

    return *pg;
}
int rimuoviPG(tabPg_t *tabPg, char *codice){
    pg_t extract;
    extract = listExtrKeyP(&tabPg->headPg,&tabPg->tailPg,codice);

    if(isVoidPg(&extract)){
        return 0;
    }
    stampaPG(stdout,&extract);
    return 1;
}
void updateStat(struct stat_s *stat, inv_t *ogg){
    stat->hp+= getHP(ogg);
    stat->mp+= getMP(ogg);
    stat->atk+= getATK(ogg);
    stat->def+= getDEF(ogg);
    stat->mag+= getMAG(ogg);
    stat->spr+= getSPR(ogg);
}
void downdateStat(struct stat_s *stat, inv_t *ogg){
    stat->hp-= getHP(ogg);
    stat->mp-= getMP(ogg);
    stat->atk-= getATK(ogg);
    stat->def-= getDEF(ogg);
    stat->mag-= getMAG(ogg);
    stat->spr-= getSPR(ogg);
}
int aggiungiEquip(pg_t *pg, inv_t *ogg){
    int i = pg->equip->inUso;
    if(i<MAXE){
        pg->equip->vettEq[i] = ogg;
        updateStat(&pg->stat,ogg);
        pg->equip->inUso++;
        return 1;
    }
    return 0;
}
void rimuoviEquip(pg_t *pg, inv_t *ogg){
    int i,j;
    for(i=0;i<pg->equip->inUso;i++){
        if(strcmp(getNameINV(pg->equip->vettEq[i]), getNameINV(ogg))==0){
            break;
        }
    }
    inv_t *t = pg->equip->vettEq[i];
    pg->equip->vettEq[i] = NULL;
    pg->equip->inUso--;
    for(j=i;j<pg->equip->inUso;j++){
        pg->equip->vettEq[j] =  pg->equip->vettEq[j+1];
    }
    downdateStat(&pg->stat,ogg);
    return;
}
void liberaPG(pg_t *pg){
    if (pg == NULL) return;
    free(pg->codice);
    free(pg->nome);
    free(pg->classe);
    liberaEquip(pg->equip);
}
void liberaListPG(tabPg_t *tabPg){
    if (tabPg == NULL) return;
    linkPg p, q;
    for(p=tabPg->headPg; p!=NULL; p=q){
        q = p->next;
        liberaPG(&(p->pg));
    }
    free(tabPg);
}
char *getNamePG(pg_t *pg){
    return pg->nome;
}
tabEquip_t *getEquipPG(pg_t *pg){
    return pg->equip;
}
int getNumEquipPG(pg_t *pg){
    return pg->equip->inUso;
}
int isInEqupPG(pg_t *pg, inv_t *ogg){
    int i;
    for(i=0;i<pg->equip->inUso;i++){
        if(pg->equip->vettEq[i] == ogg)
            return 1;
    }
    return 0;
}
pg_t *allocaPG(){
    pg_t *pg;
    pg = malloc(sizeof(pg_t)); //alloca campo stat
    initPG(pg);
    return pg;
}
void setCodicePG(pg_t *pg,char *codice){
    free(pg->codice);
    pg->codice = strdup(codice);
}
void setNomePG(pg_t *pg,char *nome){
    free(pg->nome);
    pg->nome = strdup(nome);
}
void setClassePG(pg_t *pg,char *classe){
    free(pg->classe);
    pg->classe = strdup(classe);
}
void setStatPG(pg_t *pg,int hp, int mp, int atk, int def, int mag, int spr){
    pg->stat.hp = hp;
    pg->stat.mp = mp;
    pg->stat.atk = atk;
    pg->stat.def = def;
    pg->stat.mag = mag;
    pg->stat.spr = spr;
}
