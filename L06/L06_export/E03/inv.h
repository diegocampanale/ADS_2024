//
// Created by Diego Campanale on 22/11/24.
//

#ifndef INV_H
#define INV_H

#include <stdio.h>

#define MAXL 50

typedef struct{
    char nome[MAXL];
    char tipo[MAXL];
    struct{
        int hp,mp,atk,def,mag,spr;
    }modStat;
}inv_t;

typedef struct{
    inv_t vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

void leggiFileInv(char *nomefile, tabInv_t *tabInv);
int leggiOggetto(FILE *fin, inv_t *ogg);
void stampaOggetto(FILE *fout, inv_t *ogg);


#endif // INV_H

/*
 - acquisizione da file delle informazioni relative agli oggetti disponibili, mantenendo la medesima
    struttura a vettore richiesta nel laboratorio precedente
 - ricerca di un oggetto per nome
 - stampa dei dettagli di un oggetto.
 */