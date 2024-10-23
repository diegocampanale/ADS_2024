#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define OUTPUTFILE_PATH "out.txt"
#define INPUTFILE_PATH "corse.txt"
#define STR 31

typedef enum {r_stampa, r_ord_data, r_ord_cod, r_ord_part, r_ord_arrivo, r_ricerca,r_leggi, r_fine } comando_e;
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
    voce_t *log;
    voce_t **ord_data;
    voce_t **ord_codice;
    voce_t **ord_arrivo;
    voce_t **ord_partenza;
} tabella_t;

tabella_t leggiTabella(char *filename);
comando_e leggiComando(char comandi[][STR]);
void strToLower(char *str);
void stampa(voce_t *v, int n, char riga[]);
void stampaRef(voce_t **v, int n, char *riga);
int stampaVoce(voce_t record, FILE* fileout);
void ordina_data(voce_t **v, int n);
int confrontaDate(data_t data1, data_t data2);
int confrontaOrari(ora_t ora1, ora_t ora2);
void ordina_codice(voce_t **v, int n);
int confrontaCodice(char codice1[], char codice2[]);
void ordina_partenza(voce_t **v, int n);
void ordina_arrivo(voce_t **v, int n);
void ricerca(voce_t **v,int n, char riga[]);
void leggi(tabella_t *t, char riga[]);

int main() {
    // vettore comandi del menu
    char comandi[][STR] = {"stampa", "ordina_data", "ordina_codice", "ordina_partenza", "ordina_arrivo","ricerca","leggi","fine"};
    int continua = 1;
    comando_e cmd;
    tabella_t tab;
    char riga[STR*2];

    tab = leggiTabella(INPUTFILE_PATH);

    while(continua){
        cmd = leggiComando(comandi);
        fgets(riga,30*2,stdin); /* resto della riga */
        //printf("cmd: %d%s\n", cmd, riga);
        switch (cmd) {
            case r_stampa:
                // stampa, a scelta se a video o su file, dei contenuti del log
                stampa(tab.log,tab.n_voci, riga);
                break;
            case r_ord_data:
                stampaRef(tab.ord_data,tab.n_voci,"");
                break;
            case r_ord_cod:
                stampaRef(tab.ord_codice,tab.n_voci,"");
                break;
            case r_ord_part:
                stampaRef(tab.ord_partenza,tab.n_voci,"");
                break;
            case r_ord_arrivo:
                stampaRef(tab.ord_arrivo,tab.n_voci,"");
                break;
            case r_ricerca:
                ricerca(tab.ord_partenza,tab.n_voci,riga);
                break;
            case r_leggi:
                leggi(&tab, riga);
                break;
            case r_fine:
                continua = 0;
                break;
            default: printf("Comando errato! Riprova\n");
        }
    }
    return 0;
}

void leggi(tabella_t *t, char riga[]) {
    int i;
    char nomefile[STR];
    sscanf(riga,"%s",nomefile);
    // libero il vettore di struct allocato dinamicamente (*t).log
    free(t->log);

    // libero i vettori di puntatori a struct t->og[i]
    // le struct puntate sono già state liberate precedentemente
    free(t->ord_data);
    free(t->ord_codice);
    free(t->ord_partenza);
    free(t->ord_arrivo);

    *t = leggiTabella(nomefile);
}

void ricerca(voce_t **v, int n, char riga[]) {
    // input stringa da ricercare
    char search[STR];
    sscanf(riga,"%s",search);
    strToLower(search);
    search[0] = toupper(search[0]);

    // funzione di ricerca dicotomica
    printf("Ricerca Dicotomica\n");
    int m, found=0, l=0, r=n-1, i;
    char *pos;

    while (l<=r && found == 0){
        m = (l+r)/2;
        pos = strstr(v[m]->partenza, search);
        if(pos != NULL && pos == v[m]->partenza){
            found = 1;
        }else if (strcmp(v[m]->partenza,search)<0){
            l = m+1;
        }else{
            r=m-1;
        }
    }
    if(found){
        // stampa la prima occorrenza
        stampaVoce(*v[m],stdout);

        // scorre il vettore ordinato verso SINISTRA finchè trova occorrenze
        i = m-1;
        while (i>=0 && strstr(v[i]->partenza, search) == v[i]->partenza){
            stampaVoce(*v[i],stdout);
            i--;
        }

        // scorre il vettore ordinato verso DESTRA finchè trova occorrenze
        i = m+1;
        while (i<n && strstr(v[i]->partenza, search) == v[i]->partenza) {
            stampaVoce(*v[i], stdout);
            i++;
        }
    }else{
        printf("Nessun occorrenza trovata per: %s\n",search);
    }
    printf("\n");

}

void ordina_arrivo(voce_t **v, int n) {
    // algoritmo ordinamento bubble sort
    int i,j,l=0,r=n-1,flag=1;
    voce_t *tmp;

    for (i=l; i<r && flag == 1; i++){
        flag=0;
        for (j = l; j < r-i+l; j++) {
            if (strcmp(v[j]->destinazione,v[j+1]->destinazione)>0){
                flag=1;
                tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

void ordina_partenza(voce_t **v, int n) {
    // algoritmo ordinamento bubble sort
    int i,j,l=0,r=n-1,flag=1;
    voce_t *tmp;

    for (i=l; i<r && flag == 1; i++){
        flag=0;
        for (j = l; j < r-i+l; j++) {
            if (strcmp(v[j]->partenza,v[j+1]->partenza)>0){
                flag=1;
                tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

void ordina_codice(voce_t **v, int n) {
    // funzione che confronta con bubble sort i codici delle tratte
    // Algoritmo di ordinamento BUBBLE SORT O(n^2)

    int i,j,l=0,r=n-1,flag=1;
    voce_t *tmp;

    for (i=l; i<r && flag == 1; i++){
        flag=0;
        for (j = l; j < r-i+l; j++) {
            if (confrontaCodice(v[j]->codice,v[j+1]->codice)>0){
                flag=1;
                tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
    // printf("Vettore log ordinato per codice!\n");
}

int confrontaCodice(char codice1[], char codice2[]){
    // funzione che confronta gli ultimi 3 caratteri del codice es. GTT001
    int c1 = atoi(&codice1[3]);
    int c2 = atoi(&codice2[3]);

    return c1-c2;
}

void ordina_data(voce_t **v, int n) {
    // ordinamento bubble sort
    int i, j, l=0, r=n-1, flag=1;
    voce_t *temp;

    for(i=0; i<r && flag==1; i++){
        flag=0;
        for(j=l; j<r-i+l; j++){
            if (confrontaDate(v[j]->data,v[j+1]->data)>0 || (confrontaDate(v[j]->data,v[j+1]->data)==0 && confrontaOrari(v[j]->p,v[j+1]->p)>0)){
                flag =1;
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
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

void stampaRef(voce_t **v, int n, char *riga){
    int i;
    char opt_file[3]="";

    sscanf(riga,"%s",opt_file);

    if (strcmp(opt_file,"-f") == 0){ // se l'opzione stampa su file è attiva
        FILE *fileout;
        if ((fileout = fopen(OUTPUTFILE_PATH, "w")) == NULL) {
            perror("Errore apertura file!");
            exit(-1);
        }
        for (i=0; i<n; i++){
            stampaVoce(*v[i],fileout);
        }
        fclose(fileout);
        printf("Stampa su file %s eseguita!\n", OUTPUTFILE_PATH);
    }else{ // se l'opzione stampa su file è disattiva
        for (i=0; i<n; i++){
            stampaVoce(*v[i],stdout);
        }
        printf("\n");
    }
}

void stampa(voce_t *v, int n, char riga[]) {
    int i;
    char opt_file[3];

    sscanf(riga,"%s",opt_file);

    if (strcmp(opt_file,"-f") == 0){ // se l'opzione stampa su file è attiva
        FILE *fileout;
        if ((fileout = fopen(OUTPUTFILE_PATH, "w")) == NULL) {
            perror("Errore apertura file!");
            exit(-1);
        }
        for (i=0; i<n; i++){
            stampaVoce(v[i],fileout);
        }
        fclose(fileout);

    }else{ // se l'opzione stampa su file è disattiva
        for (i=0; i<n; i++){
            stampaVoce(v[i],stdout);
        }
        printf("\n");
    }
}

int stampaVoce(voce_t record, FILE* fileout) {
    int n = fprintf(fileout, "%-10s %-18s %-18s %04d/%02d/%02d   %02d:%02d:%02d      %02d:%02d:%02d      %-8d\n",
            record.codice,
            record.partenza,
            record.destinazione,
            record.data.aa, record.data.mm, record.data.gg,
            record.p.h, record.p.m, record.p.s,
            record.d.h, record.d.m, record.d.s,
            record.ritardo);
    return n;
}

tabella_t leggiTabella(char *filename){
    int i, n;
    tabella_t tab;

    FILE *fin = fopen(filename, "r");
    if(fin == NULL)
        exit(-1);

    fscanf(fin,"%d", &tab.n_voci);
    tab.log = (voce_t *) malloc(tab.n_voci*sizeof (voce_t));

    tab.ord_data = (voce_t **) malloc(tab.n_voci*sizeof (voce_t *));
    tab.ord_codice = (voce_t **) malloc(tab.n_voci*sizeof (voce_t *));
    tab.ord_partenza = (voce_t **) malloc(tab.n_voci*sizeof (voce_t *));
    tab.ord_arrivo = (voce_t **) malloc(tab.n_voci*sizeof (voce_t *));

    for (i=0; i<tab.n_voci; i++){
        fscanf(fin, " %s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].data_str, tab.log[i].orap_str, tab.log[i].orad_str, &tab.log[i].ritardo);
        sscanf (tab.log[i].data_str,"%d/%d/%d", &tab.log[i].data.aa,&tab.log[i].data.mm,&tab.log[i].data.gg);
        sscanf (tab.log[i].orap_str,"%d:%d:%d", &tab.log[i].p.h,&tab.log[i].p.m,&tab.log[i].p.s);
        sscanf (tab.log[i].orad_str,"%d:%d:%d", &tab.log[i].d.h,&tab.log[i].d.m,&tab.log[i].d.s);
    }
    fclose(fin);

    // assegno gli indirizzi delle struct originarie ai vettori di puntatori a struct
    for(int i=0; i<tab.n_voci; i++) {
        tab.ord_data[i] = &tab.log[i];
        tab.ord_codice[i] = &tab.log[i];
        tab.ord_arrivo[i] = &tab.log[i];
        tab.ord_partenza[i] = &tab.log[i];
    }

    // ordinamento vettori di puntatori a struct
    ordina_data(tab.ord_data, tab.n_voci);
    ordina_codice(tab.ord_codice,tab.n_voci);
    ordina_partenza(tab.ord_partenza,tab.n_voci);
    ordina_arrivo(tab.ord_arrivo,tab.n_voci);

    return tab;
}

comando_e leggiComando(char comandi[][STR]){
    comando_e cmd;
    int c=0, continua=0;
    char riga[100], comando[STR];

    printf("Menu:\n- stampa [-f]\n- ordina_data\n- ordina_codice\n- ordina_partenza\n- ordina_arrivo\n- ricerca [stazione_partenza]\n- leggi [nomefile.txt]\n- fine\n--> ");
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