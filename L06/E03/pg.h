//
// Created by Diego Campanale on 22/11/24.
//

#ifndef PG_H
#define PG_H

#include <stdio.h>
#include "inv.h"

#define MAXS 50
#define MAXC 50

typedef struct{
    char codice[MAXC];
    char nome[MAXS];
    char classe[MAXS];
    int *equip;
    struct{
        unsigned int hp, mp,atk,def,mag,spr;
    }stat;
}pg_t;

typedef struct node_s *linkPg, nodePg_t;
typedef struct node_s{
    pg_t pg;
    linkPg next;
};

typedef struct{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
}tabPg_t;

void leggiFilePG(char *nomefile, tabPg_t *tabPg);
int leggiPG(FILE *fin, pg_t *pg);
void stampaPG(FILE *fin, pg_t *pg);

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