#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "pg.h"
#include "inv.h"

#define INPUTPG_PATH "pg.txt"
#define INPUTINV_PATH "inventario.txt"
#define MAXS 51
#define MAXC 7

typedef enum{r_loadPG,r_loadINV,r_addPG,r_removePG,r_modifyEquip,r_displayPG,r_end}comando_e;

void printMenu();
int leggiNuovoPG(tabPg_t **pTabPg);
int eliminaPG(tabPg_t *tabPg);
int modificaEquip(tabPg_t *tabPg, tabInv_t *tabInv);
void leggiCodice(char *codice);
int displayPG(tabPg_t *tabPg, tabInv_t *tabInv);

int main(int argc, char ** argv){
    int i;
    char buf[MAXS];
    tabPg_t *tPg = NULL;
    tabInv_t *tInv = NULL;

    comando_e cmd;
    int continua = 1, n;



    while (continua){
        //Menu
        cmd = r_end;
        printMenu();
        scanf(" %d",&cmd);

        switch (cmd) {
            case r_loadPG:
                n= leggiFilePG(&tPg,INPUTPG_PATH);
                if(tPg==NULL)
                    printf("Errore apertura file %s\n",INPUTPG_PATH);
                else
                    printf("%d personaggi nuovi caricati\n",n);
                break;

            case r_loadINV:
                n= leggiFileInv(&tInv, INPUTINV_PATH);
                if(tInv==NULL)
                    printf("Errore apertura file %s\n",INPUTINV_PATH);
                else
                    printf("%d oggetti caricati correttamente\n", n);
                break;

            case r_addPG:
                n = leggiNuovoPG(&tPg);
                if(n==1){
                    printf("Personaggio aggiunto correttamente\n");
                }else if(n==0){
                    printf("Personaggio esistente aggiornato!\n");
                }else{
                    printf("Errore. Personaggio non aggiunto! \n");
                }
                break;

            case r_removePG:
                if(eliminaPG(tPg)==0){
                    printf("Inesistente\n");
                }
                break;

            case r_modifyEquip:
                if(modificaEquip(tPg,tInv)==0){
                    printf("Errore\n");
                }
                break;
            case r_displayPG:
                if(displayPG(tPg,tInv)==0){
                    printf("Errore\n");
                }
                break;
            case r_end:
                continua = 0;
                break;
            default:
                printf("Opzione non valida.\n");
                break;
        }
        fgets(buf,MAXS,stdin);
    }

    liberaListPG(tPg);
    liberaInv(tInv);

    return 0;
}

void printMenu(void){
    int i=0, r;
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

int leggiNuovoPG(tabPg_t **pTabPg){
    char *codice,*nome,*classe;
    codice= malloc(MAXC);
    nome= malloc(MAXS);
    classe= malloc(MAXS);

    int hp,mp,atk,def,mag,spr;
    int r;

    printf("Codice: "); leggiCodice(codice);
    if(*codice=='\0') { return 0; }
    printf("Nome: "); scanf(" %s",nome);
    printf("Classe: "); scanf(" %s",classe);
    printf("Statistiche <hp> <mp> <atk> <def> <mag> <spr>: ");
    if (scanf(" %d %d %d %d %d %d", &hp, &mp, &atk, &def, &mag, &spr) != 6) {
        return 0; // Esci con errore
    }
    if (hp < 0 || mp < 0 || atk < 0 || def < 0 || mag < 0 || spr < 0) {
        return 0;
    }

    pg_t *pg = allocaPG();
    setCodicePG(pg,codice);
    setNomePG(pg,nome);
    setClassePG(pg,classe);
    setStatPG(pg,hp,mp,atk,def,mag,spr);

    r = aggiungiPG(pTabPg,pg);

    free(codice);
    free(nome);
    free(classe);
    liberaPG(pg);

    return r;
}

int eliminaPG(tabPg_t *tabPg){
    char codice[MAXC];
    printf("Codice personaggio da cancellare: ");
    scanf(" %s",codice);
    if(codice[0]=='P'&&codice[1]=='G'&& isnumber(codice[2])&& isnumber(codice[3])&& isnumber(codice[4])&& isnumber(codice[5])) {
        printf("Personaggio rimosso: \n");
        if (rimuoviPG(tabPg, codice) != 0) {
            return 1;
        }
    }
    return 0; // personaggio non trovato
}

int modificaEquip(tabPg_t *tabPg, tabInv_t *tabInv){
    if(tabPg==NULL){
        printf("Lista personaggi non esistente\n");
        return 0;
    }
    if(tabInv==NULL){
        printf("Inventario oggetti non esistente\n");
        return 0;
    }

    char *codice = malloc(MAXC);
    char *nome;
    inv_t **Pogg;
    pg_t **Ppg;

    int opt,i;

    printf("Codice personaggio da Modificare: "); leggiCodice(codice);
    if(codice==NULL)
        return 0;
    Ppg = cercaPgPunt(tabPg,codice);
    if(Ppg==NULL)
        return 0;
    free(codice);
    printf("Personaggio selezionato:\n");
    stampaPG(stdout,*Ppg);

    printf("Seleziona un opzione:\n");
    printf("1. Aggiungi oggetto all'equipaggiamento di %s\n", getNamePG(*Ppg));
    printf("2. Rimuvi oggetto dall'equipaggiamento di %s\n", getNamePG(*Ppg));
    printf(">> ");
    scanf(" %d",&opt);
    switch (opt) {
        case 1:
            nome = malloc(MAXS);
            Pogg = malloc(sizeof(inv_t *));
            if(getNumEquipPG(*Ppg)>0){
                printf("Equipaggiamento corrente di %s:\n", getNamePG(*Ppg));
                stampaEquip(stdout, getEquipPG(*Ppg));
            }else{
                printf("%s non ha oggetti equipaggiati.\n", getNamePG(*Ppg));
            }
            if(numINV(tabInv)>0){
                printf("Oggetti Disponibili:\n");
                stampaOggetti(stdout,tabInv);
            }else{
                return 0;
            }
            printf("Nome oggetto da aggiungere:\n>> ");
            scanf(" %s",nome);
            *Pogg = cercaOggetto(tabInv,nome);
            if(isInEqupPG(*Ppg,*Pogg)==0){
                aggiungiEquip(*Ppg,*Pogg);
                printf("Oggetto aggiunto correttamente all'equipaggiamento di %s\n", getNamePG(*Ppg));
            }else{
                printf("Oggetto già equipaggiato da %s\n", getNamePG(*Ppg));
            }
            stampaPG(stdout,*Ppg);
            free(nome);
            free(Pogg);
            break;
        case 2:
            nome = malloc(MAXS);
            Pogg = malloc(sizeof(inv_t *));
            if(getNumEquipPG(*Ppg)>0){
                printf("Equipaggiamento corrente di %s:\n", getNamePG(*Ppg));
                stampaEquip(stdout, getEquipPG(*Ppg));

                printf("Nome oggetto da rimuovere:\n>> ");
                scanf(" %s",nome);
                *Pogg = cercaOggetto(tabInv,nome);
                if(isInEqupPG(*Ppg,*Pogg)==1){
                    rimuoviEquip(*Ppg,*Pogg);
                    printf("Oggetto rimosso correttamente dall'equipaggiamento di %s\n", getNamePG(*Ppg));
                }else{
                    printf("Oggetto non equipaggiato da %s\n", getNamePG(*Ppg));
                }
                stampaPG(stdout,*Ppg);
            }else{
                printf("%s non ha oggetti equipaggiati.\n", getNamePG(*Ppg));
            }
            free(nome);
            free(Pogg);
            break;
        default:
            free(Ppg);
            return 0;
    }

    free(Ppg);
    return 1;
}

void leggiCodice(char *codice){
    scanf(" %s",codice);
    if(codice[0]!='P' || codice[1]!='G'|| !isnumber(codice[2])|| !isnumber(codice[3])|| !isnumber(codice[4])|| !isnumber(codice[5]))
        *codice = '\0';
}

int displayPG(tabPg_t *tabPg, tabInv_t *tabInv){
    if(tabPg==NULL){
        printf("Lista personaggi non esistente\n");
        return 0;
    }

    char *codice = malloc(MAXC);
    pg_t **Ppg = malloc(sizeof(pg_t*));
    printf("Codice personaggio da Visualizzare: "); leggiCodice(codice);
    if(codice==NULL)
        return 0;
    *Ppg = cercaPG(tabPg,codice);
    if(*Ppg==NULL)
        return 0;
    free(codice);
    stampaPG(stdout,*Ppg);
    free(Ppg);
    return 1;
}