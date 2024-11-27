#ifndef PG_H
#define PG_H

#include <stdio.h>
#include "inv.h"


typedef struct tabEquip_s tabEquip_t;
typedef struct pg_s pg_t;
typedef struct nodePg_s *linkPg, nodePg_t;
typedef struct tabPg_s tabPg_t;

tabPg_t *leggiFilePG(char *nomefile);
void stampaPG(FILE *fin, pg_t *pg);
void liberaPG(tabPg_t *tabPg);
tabPg_t *allocaPG();
int numPG(tabPg_t *tabPg);


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