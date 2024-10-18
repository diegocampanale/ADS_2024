#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define OUTPUTFILE_PATH "./out.txt"
#define INPUTFILE_PATH "./corse.txt"
#define STR 31
#define MAXR 1000

typedef enum {r_stampa, r_ord_data, r_ord_cod, r_ord_part, r_ord_arrivo, r_ricerca, r_fine } comando_e;
typedef struct { int gg; int mm; int aa } data_t;
typedef struct { int h; int m; int s} ora_t;
typedef struct {
    char codice[STR];
    char partenza[STR];
    char destinazione[STR];
    char data_str[STR];
    char orap_str[STR];
    char orad_str[STR];
    int ritardo;
    data_t data;
    ora_t p, d;
} voce_t;
typedef struct {
    int n_voci;
    voce_t log[MAXR];
} tabella_t;
typedef struct {
    int n_voci;
    voce_t *log[MAXR];
} r_tabella_t;

tabella_t leggiTabella();
comando_e leggiComando(char comandi[][STR]);
void strToLower(char *str);
void stampa(tabella_t tab, char riga[31]);
void stampaRef(r_tabella_t tab, char riga[31]);
void stampaVoce(voce_t record, FILE* fileout);
r_tabella_t ordina_data(r_tabella_t tab);
int confrontaDate(data_t data1, data_t data2);
int confrontaOrari(ora_t ora1, ora_t ora2);
r_tabella_t ordina_codice(r_tabella_t tab);
int confrontaCodice(char codice1[], char codice2[]);
r_tabella_t ordina_partenza(r_tabella_t tab);
r_tabella_t ordina_arrivo(r_tabella_t tab);
void ricerca(r_tabella_t tab, char riga[31]);

int main() {
    // vettore comandi del menu
    char comandi[][STR] = {"stampa", "ordina_data", "ordina_codice", "ordina_partenza", "ordina_arrivo","ricerca", "fine"};
    int continua = 1;
    comando_e cmd;
    tabella_t tab;
    char riga[STR*2-1];

    tab = leggiTabella();

    //voce_t *v_ord_data[MAXR],*v_ord_codice[MAXR],*v_ord_partenza[MAXR], *v_ord_arrivo[MAXR];
    r_tabella_t tab_ord_data, tab_ord_codice, tab_ord_partenza, tab_ord_arrivo;
    // ricopio n elementi struct
    tab_ord_data.n_voci = tab.n_voci;
    tab_ord_codice.n_voci = tab.n_voci;
    tab_ord_arrivo.n_voci = tab.n_voci;
    tab_ord_partenza.n_voci = tab.n_voci;

    // assegno gli indirizzi delle struct originarie ai vettori di puntatori a struct
    for(int i=0; i<tab.n_voci; i++) {
        tab_ord_data.log[i] = &tab.log[i];
        tab_ord_codice.log[i] = &tab.log[i];
        tab_ord_arrivo.log[i] = &tab.log[i];
        tab_ord_partenza.log[i] = &tab.log[i];
    }

    // ordinamento vettori di puntatori a struct
    tab_ord_data = ordina_data(tab_ord_data);
    tab_ord_codice = ordina_codice(tab_ord_codice);
    tab_ord_partenza = ordina_partenza(tab_ord_partenza);
    tab_ord_arrivo = ordina_arrivo(tab_ord_arrivo);

    while(continua){
        cmd = leggiComando(comandi);
        fgets(riga,30*2,stdin); /* resto della riga */
        //printf("cmd: %d%s\n", cmd, riga);
        switch (cmd) {
            case r_stampa:
                // stampa, a scelta se a video o su file, dei contenuti del log
                stampa(tab, riga);
                break;
            case r_ord_data:
                stampaRef(tab_ord_data,"");
                break;
            case r_ord_cod:
                stampaRef(tab_ord_codice,"");
                break;
            case r_ord_part:
                stampaRef(tab_ord_partenza,"");
                break;
            case r_ord_arrivo:
                stampaRef(tab_ord_arrivo,"");
                break;
            case r_ricerca:
                ricerca(tab_ord_partenza,riga);
                break;
            case r_fine:
                continua = 0;
                break;
            default: printf("Comando errato! Riprova\n");
        }
    }
    return 0;
}

void ricerca(r_tabella_t tab, char riga[31]) {
    // input stringa da ricercare
    char search[STR];
    sscanf(riga,"%s",search);
    strToLower(search);
    search[0] = toupper(search[0]);

    // funzione di ricerca dicotomica
    // ricerca dicotomica
    printf("Ricerca Dicotomica\n");
    int m, found=0, l=0, r=tab.n_voci-1, i;
    char *pos;

    while (l<=r && found == 0){
        m = (l+r)/2;
        pos = strstr(tab.log[m]->partenza, search);
        if(pos != NULL && pos == tab.log[m]->partenza){
            found = 1;
        }else if (strcmp(tab.log[m]->partenza,search)<0){
            l = m+1;
        }else{
            r=m-1;
        }
    }
    if(found){
        // stampa la prima occorrenza
        stampaVoce(*tab.log[m],stdout);

        // scorre il vettore ordinato verso SINISTRA finchè trova occorrenze
        i = m-1;
        while (i>=0 && strstr(tab.log[i]->partenza, search) == tab.log[i]->partenza){
            stampaVoce(*tab.log[i],stdout);
            i--;
        }

        // scorre il vettore ordinato verso DESTRA finchè trova occorrenze
        i = m+1;
        while (i<tab.n_voci && strstr(tab.log[i]->partenza, search) == tab.log[i]->partenza) {
            stampaVoce(*tab.log[i], stdout);
            i++;
        }
    }else{
        printf("Nessun occorrenza trovata per: %s\n",search);
    }
    printf("\n");

}

r_tabella_t ordina_arrivo(r_tabella_t tab) {
    // algoritmo ordinamento bubble sort
    int i,j,l=0,r=tab.n_voci-1,flag=1;
    voce_t *tmp;

    for (i=l; i<r && flag == 1; i++){
        flag=0;
        for (j = l; j < r-i+l; j++) {
            if (strcmp(tab.log[j]->destinazione,tab.log[j+1]->destinazione)>0){
                flag=1;
                tmp = tab.log[j];
                tab.log[j] = tab.log[j+1];
                tab.log[j+1] = tmp;
            }
        }
    }
    // printf("Vettore log ordinato per stazione di arrivo!\n");
    return tab;
}

r_tabella_t ordina_partenza(r_tabella_t tab) {
    // algoritmo ordinamento bubble sort
    int i,j,l=0,r=tab.n_voci-1,flag=1;
    voce_t *tmp;

    for (i=l; i<r && flag == 1; i++){
        flag=0;
        for (j = l; j < r-i+l; j++) {
            if (strcmp(tab.log[j]->partenza,tab.log[j+1]->partenza)>0){
                flag=1;
                tmp = tab.log[j];
                tab.log[j] = tab.log[j+1];
                tab.log[j+1] = tmp;
            }
        }
    }
    // printf("Vettore log ordinato per stazione di partenza!\n");
    return tab;
}

r_tabella_t ordina_codice(r_tabella_t tab) {
    // funzione che confronta con bubble sort i codici delle tratte e restituisce tab
    // Algoritmo di ordinamento BUBBLE SORT O(n^2)

    int i,j,l=0,r=tab.n_voci-1,flag=1;
    voce_t *tmp;

    for (i=l; i<r && flag == 1; i++){
        flag=0;
        for (j = l; j < r-i+l; j++) {
            if (confrontaCodice(tab.log[j]->codice,tab.log[j+1]->codice)>0){
                flag=1;
                tmp = tab.log[j];
                tab.log[j] = tab.log[j+1];
                tab.log[j+1] = tmp;
            }
        }
    }
    // printf("Vettore log ordinato per codice!\n");
    return tab;
}

int confrontaCodice(char codice1[], char codice2[]){
    // funzione che confronta gli ultimi 3 caratteri del codice es. GTT001
    int c1 = atoi(&codice1[3]);
    int c2 = atoi(&codice2[3]);

    return c1-c2;
}

r_tabella_t ordina_data(r_tabella_t tab) {
    // ordinamento bubble sort
    int i, j, l=0, r=tab.n_voci-1, flag=1;
    voce_t *temp;

    for(i=0; i<r && flag==1; i++){
        flag=0;
        for(j=l; j<r-i+l; j++){
            if (confrontaDate(tab.log[j]->data,tab.log[j+1]->data)>0 || (confrontaDate(tab.log[j]->data,tab.log[j+1]->data)==0 && confrontaOrari(tab.log[j]->p,tab.log[j+1]->p)>0)){
                flag =1;
                temp = tab.log[j];
                tab.log[j] = tab.log[j+1];
                tab.log[j+1] = temp;
            }
        }
    }
    // printf("vettore log ordinato per data!\n");
    return tab;
}

int confrontaDate(data_t data1, data_t data2){
    if (data1.aa > data2.aa) {
        return 1;
    } else if (data1.aa < data2.aa) {
        return -1;
    } else {  // gli anni sono uguali
        if (data1.mm > data2.mm) {
            return 1;
        } else if (data1.mm < data2.mm) {
            return -1;
        } else {  // i mesi sono uguali
            if (data1.gg > data2.gg) {
                return 1;
            } else if (data1.gg < data2.gg){
                return -1;
            } else{ // i giorni sono uguali
                return 0;
            }
        }
    }
}

int confrontaOrari(ora_t ora1, ora_t ora2){
    if (ora1.h > ora2.h){
        return 1;
    }else if (ora1.h < ora2.h){
        return -1;
    }else{ // le ore sono uguali
        if (ora1.m > ora2.m){
            return 1;
        }else if (ora1.m < ora2.m){
            return -1;
        }else { // i minuti sono uguali
            if (ora1.s > ora2.s){
                return 1;
            }else if (ora1.s < ora2.s){
                return -1;
            }else { // i secondi sono uguali
                return 0;
            }
        }
    }
}

void stampaRef(r_tabella_t tab, char riga[31]){
    int i;
    char opt_file[STR];

    sscanf(riga,"%s",opt_file);

    if (strcmp(opt_file,"-f") == 0){ // se l'opzione stampa su file è attiva
        FILE *fileout;
        if ((fileout = fopen(OUTPUTFILE_PATH, "w")) == NULL) {
            perror("Errore apertura file!");
            exit(-1);
        }
        for (i=0; i<tab.n_voci; i++){
            stampaVoce(*(tab.log[i]),fileout);
        }
        fclose(fileout);
        printf("Stampa su file %s eseguita!\n", OUTPUTFILE_PATH);
    }else{ // se l'opzione stampa su file è disattiva
        for (i=0; i<tab.n_voci; i++){
            stampaVoce(*tab.log[i],stdout);
        }
        printf("\n");
    }
}

void stampa(tabella_t tab, char riga[31]) {
    int i;
    char opt_file[STR];

    sscanf(riga,"%s",opt_file);

    if (strcmp(opt_file,"-f") == 0){ // se l'opzione stampa su file è attiva
        FILE *fileout;
        if ((fileout = fopen(OUTPUTFILE_PATH, "w")) == NULL) {
            perror("Errore apertura file!");
            exit(-1);
        }
        for (i=0; i<tab.n_voci; i++){
            stampaVoce(tab.log[i],fileout);
        }
        fclose(fileout);
        printf("Stampa su file %s eseguita!\n", OUTPUTFILE_PATH);
    }else{ // se l'opzione stampa su file è disattiva
        for (i=0; i<tab.n_voci; i++){
            stampaVoce(tab.log[i],stdout);
        }
        printf("\n");
    }
}

void stampaVoce(voce_t record, FILE* fileout) {
    fprintf(fileout, "%-10s %-15s %-15s %04d/%02d/%02d   %02d:%02d:%02d      %02d:%02d:%02d      %-8d\n",
            record.codice,
            record.partenza,
            record.destinazione,
            record.data.aa, record.data.mm, record.data.gg,
            record.p.h, record.p.m, record.p.s,
            record.d.h, record.d.m, record.d.s,
            record.ritardo);
}

tabella_t leggiTabella(){
    int i, n;
    tabella_t tab;

    FILE *fin = fopen(INPUTFILE_PATH, "r");
    if(fin == NULL)
        exit(-1);

    fscanf(fin,"%d", &tab.n_voci);
    for (i=0; i<tab.n_voci; i++){
        fscanf(fin, " %s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].data_str, tab.log[i].orap_str, tab.log[i].orad_str, &tab.log[i].ritardo);
        sscanf (tab.log[i].data_str,"%d/%d/%d", &tab.log[i].data.aa,&tab.log[i].data.mm,&tab.log[i].data.gg);
        sscanf (tab.log[i].orap_str,"%d:%d:%d", &tab.log[i].p.h,&tab.log[i].p.m,&tab.log[i].p.s);
        sscanf (tab.log[i].orad_str,"%d:%d:%d", &tab.log[i].d.h,&tab.log[i].d.m,&tab.log[i].d.s);
    }
    return tab;
}

comando_e leggiComando(char comandi[][STR]){
    comando_e cmd;
    int c=0, continua=0;
    char riga[100], comando[STR];

    printf("Menu:\n- stampa [-f]\n- ordina_data\n- ordina_codice\n- ordina_partenza\n- ordina_arrivo\n- ricerca [stazione_partenza]\n- fine\n--> ");
    scanf("%s",comando); // read only cmd
    printf("\n");
    strToLower(comando);
    cmd = r_stampa;
    while(cmd<=r_fine && strcmp(comando,comandi[cmd])!=0) {
        //printf("%s\n", comandi[cmd]);
        cmd++;
    }
    return cmd;
}

void strToLower(char *str) {
    int size = strlen(str);
    for (int i = 0; i<size; i++){
        str[i] = tolower(str[i]);
    }
    return;
}