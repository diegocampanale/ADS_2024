#include <stdio.h>
#include "pg.h"
#include "inv.h"

#define INPUTPG_PATH "pg.txt"
#define INPUTINV_PATH "inventario.txt"
#define MAXS 51
#define MAXC 7

typedef enum{r_loadPG,r_loadINV,r_addPG,r_removePG,r_modifyEquip,r_displayPG,r_end}comando_e;

void printMenu();
int leggiNuovoPG(tabPg_t *tabPg);

int main(int argc, char ** argv){
    int i;
    tabPg_t *tPg = NULL;
    tabInv_t *tInv = NULL;

    comando_e cmd;
    int continua = 1;



    while (continua){
        //Menu
        printMenu();
        scanf(" %d",&cmd);

        switch (cmd) {
            case r_loadPG:
                if(tPg != NULL){
                    liberaListPG(tPg);
                    tPg = NULL;
                }
                tPg = leggiFilePG(INPUTPG_PATH);
                if(tPg==NULL)
                    printf("Errore apertura file %s\n",INPUTPG_PATH);
                else
                    printf("%d personaggi caricati correttamente\n",numPG(tPg));
                break;

            case r_loadINV:
                if(tInv!= NULL){
                    liberaInv(tInv);
                    tInv = NULL;
                }
                tInv = leggiFileInv(INPUTINV_PATH);
                if(tInv==NULL)
                    printf("Errore apertura file %s\n",INPUTINV_PATH);
                else
                    printf("%d oggetti caricati correttamente\n", numINV(tInv));
                break;

            case r_addPG:
                if(leggiNuovoPG(tPg) == 1){
                    printf("Personaggio aggiunto correttamente\n");
                }else{
                    printf("Errore. Personaggio non aggiunto! \n");
                }
                break;

            case r_removePG:
                break;
            case r_modifyEquip:
                break;
            case r_displayPG:
                break;
            case r_end:
                continua = 0;
                break;
            default:
                printf("Opzione non valida.\n");
                break;
        }
    }






    liberaListPG(tPg);
    liberaInv(tInv);

    return 0;
}

void printMenu(void){
    int i=0;
    printf("\nMenu:\n");
    printf("%d. Carica Lista Personaggi\n",i++);
    printf("%d. Carica Elenco Oggetti\n",i++);
    printf("%d. Aggiungi Nuovo Personaggio\n",i++);
    printf("%d. Elimina Personaggio\n",i++);
    printf("%d. Modifica Equipaggiamento Personaggio\n",i++);
    printf("%d. Visualizza Statistiche Personaggio\n",i++);
    printf("%d. Esci\n",i);
    printf(">> ");
}

int leggiNuovoPG(tabPg_t *tabPg){
    char codice[MAXC],nome[MAXS],classe[MAXS];
    int hp,mp,atk,def,mag,spr;
    printf("Codice: "); scanf(" %s",codice);
    printf("Nome: "); scanf(" %s",nome);
    printf("Classe: "); scanf(" %s",classe);
    printf("Statistiche <hp> <mp> <atk> <def> <mag> <spr>: "); scanf(" %d %d %d %d %d %d",&hp,&mp,&atk,&def,&mag,&spr);
    return aggiungiPG(tabPg,codice,nome,classe,hp,mp,atk,def,mag,spr);
}