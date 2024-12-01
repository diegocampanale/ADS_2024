#ifndef PG_H
#define PG_H

#include <stdio.h>
#include "inv.h"


typedef struct tabEquip_s tabEquip_t;
typedef struct pg_s pg_t;
typedef struct nodePg_s *linkPg, nodePg_t;
typedef struct tabPg_s tabPg_t;

int leggiFilePG(tabPg_t **pTabPg,char *nomefile);
void stampaPG(FILE *fin, pg_t *pg);
void liberaListPG(tabPg_t *tabPg);
tabPg_t *allocaTabPG();
int numPG(tabPg_t *tabPg);
int aggiungiPG(tabPg_t **tabPg, pg_t *pg);
int rimuoviPG(tabPg_t *tabPg, char *codice);
void stampaListPG(FILE *fout,tabPg_t *tabPg);
pg_t *cercaPG(tabPg_t *tabPg, char *codice);
int aggiungiEquip(pg_t *pg, inv_t *ogg);
void rimuoviEquip(pg_t *pg, inv_t *ogg);
char *getNamePG(pg_t *pg);
void stampaEquip(FILE *f,tabEquip_t *equip);
tabEquip_t *getEquipPG(pg_t *pg);
int getNumEquipPG(pg_t *pg);
int isInEqupPG(pg_t *pg, inv_t *ogg);
pg_t *allocaPG();
void liberaPG(pg_t *pg);
void PGcpy(pg_t *dest, pg_t *src);
pg_t **cercaPgPunt(tabPg_t *tabPg, char *codice);

void setCodicePG(pg_t *pg,char *codice);
void setNomePG(pg_t *pg,char *nome);
void setClassePG(pg_t *pg,char *classe);
void setStatPG(pg_t *pg,int hp, int mp, int atk, int def, int mag, int spr);


#endif // PG_H

/*
- acquisizione da file delle informazioni dei personaggi, mantenendo la medesima
  struttura a lista richiesta nel laboratorio precedente
- inserimento/cancellazione di un personaggio
- ricerca per codice di un personaggio
- stampa dei dettagli di un personaggio e del relativo equipaggiamento, se presente
- modifica dell’equipaggiamento di un personaggio
    - aggiunta/rimozione di un oggetto.
 *
 */