#include <stdio.h>
#include "pg.h"
#include "inv.h"

#define INPUTFILE_PATH "pg.txt"

int main(int argc, char ** argv){

    tabPg_t *tPg;
    tabInv_t *tInv;
    leggiFilePG(INPUTFILE_PATH,tPg);
    printf("\n");
    tInv = leggiFileInv("inventario.txt");

    liberaInv(tInv);

    return 0;
}
