#include <stdio.h>
#include "pg.h"
#include "inv.h"

#define INPUTFILE_PATH "pg.txt"

int main(int argc, char ** argv){

    tabPg_t *tPg;
    tPg = leggiFilePG(INPUTFILE_PATH);

    printf("\n");

    tabInv_t *tInv;
    tInv = leggiFileInv("inventario.txt");
    stampaOggetto(stdout, cercaOggetto(tInv,"TalismanoNero"));
    liberaInv(tInv);

    return 0;
}
