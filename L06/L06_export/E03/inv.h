#ifndef INV_H
#define INV_H

#include <stdio.h>

typedef struct modStat_s modStat_t;
typedef struct inv_s inv_t;
typedef struct tabInv_s tabInv_t;

tabInv_t *leggiFileInv(char *nomefile);
inv_t *cercaOggetto(tabInv_t *tabInv, char *nome);
void stampaOggetto(FILE *fout, inv_t *ogg);
tabInv_t *allocaInv(int max);
void liberaInv(tabInv_t *tabInv);
int getHP(inv_t *ogg);
int getMP(inv_t *ogg);
int getATK(inv_t *ogg);
int getDEF(inv_t *ogg);
int getMAG(inv_t *ogg);
int getSPR(inv_t *ogg);
int numINV(tabInv_t *tabInv);


#endif //INV_H


/*
 - acquisizione da file delle informazioni relative agli oggetti disponibili, mantenendo la medesima
    struttura a vettore richiesta nel laboratorio precedente
 - ricerca di un oggetto per nome
 - stampa dei dettagli di un oggetto.

 #define M1 40
#define M2 8

typedef struct aeroporti_s aeroporti_t;
typedef struct voli_s voli_t;

int cercaAeroportoC(aeroporti_t *aeroporti, char *codice);
char *codiceAeroporto(aeroporti_t *aeroporti, int id);
void liberaAeroporti (aeroporti_t *ap);
void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti);
void generaPartenzeArrivi (aeroporti_t *aeroporti, voli_t *voli);
void scriviPartenzeArrivi (char *nomeFile, aeroporti_t *aeroporti, voli_t *voli);
aeroporti_t *allocaAeroporti (int max);
aeroporti_t *leggiAeroporti (char *nomeFile);

*/