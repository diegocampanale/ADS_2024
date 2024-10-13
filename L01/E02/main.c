#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INPUTFILE_PATH "./corse.txt"
#define STR 31
#define MAXR 1000

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine } comando_e;
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

tabella_t leggiTabella();
comando_e leggiComando(char comandi[][STR]);
void strToLower(char *str);
void date(tabella_t tab, char riga[]);
int confrontaDate(data_t data1, data_t data2);
void stampaVoce(voce_t record);
void partenze(tabella_t tab, char riga[]);
void capolinea(tabella_t tab, char riga[]);
void ritardo(tabella_t tab, char riga[]);
void ritardo_tot(tabella_t tab, char riga[]);

int main() {
    // vettore comandi del menu
    char comandi[][STR] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    int continua = 1;
    comando_e cmd;
    tabella_t tab;
    char riga[STR*2-1];

    tab = leggiTabella();
    while(continua){
        cmd = leggiComando(comandi);
        fgets(riga,30*2,stdin); /* resto della riga */
        switch (cmd) {
            case r_date:
                // Elenco di tutte le corse partite in un certo intervallo di date
                date(tab, riga);
                break;
            case r_partenza:
                // Elenco di tutti le corse partite da una certa fermata (partenza)
                partenze(tab, riga);
                break;
            case r_capolinea:
                // elenco di tute le corse che fanno capolinea in una certa fermata
                capolinea(tab,riga);
                break;
            case r_ritardo:
                // elenco di tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date
                ritardo(tab,riga);
                break;
            case r_ritardo_tot:
                // elenco del ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta
                ritardo_tot(tab,riga);
                break;
            case r_fine:
                continua = 0;
                break;
            default: perror("Comando errato! Riprova\n");
        }
    }
    return 0;
}

void ritardo_tot(tabella_t tab, char riga[]) {
    char codice[STR];
    sscanf(riga," %s", codice);
    int i, sum=0, trovato=0;

    for(i=0; i<tab.n_voci; i++){
        if (!strcmp(codice,tab.log[i].codice)){
            trovato = 1;
            sum += tab.log[i].ritardo;
        }
    }
    if (trovato) printf("Ritardo totale per la corsa %s: %d\n",codice,sum);
}

void ritardo(tabella_t tab, char riga[]) {
    data_t data_start, data_end;
    int i;
    if (sscanf (riga,"%d/%d/%d %d/%d/%d", &data_start.aa, &data_start.mm, &data_start.gg, &data_end.aa, &data_end.mm, &data_end.gg)!=6){
        perror("Formato date errato");
        exit(-1);
    }
    printf("Elenco di tutte le corse che hanno raggiunto la destinazione in ritardo, tra il %04d/%02d/%02d e il %04d/%02d/%02d\n", data_start.aa, data_start.mm, data_start.gg, data_end.aa, data_end.mm, data_end.gg);

    // etichette stampa
    printf("%-10s %-15s %-15s %-12s %-13s %-13s %-8s\n","Codice", "Partenza", "Destinazione", "Data", "Ora Part.", "Ora Arr.", "Ritardo");
    printf("-------------------------------------------------------------------------------------------\n");

    for (i=0; i<tab.n_voci; i++){
        //Controllo data_start<data_record
        if (confrontaDate(data_start,data_end)){
            perror("Range date invalido");
            exit(-1);
        }
        if(tab.log[i].ritardo>0){
            if (confrontaDate(tab.log[i].data, data_start) && confrontaDate(data_end, tab.log[i].data)){
                stampaVoce(tab.log[i]);
            }
        }
    }
}

void capolinea(tabella_t tab, char riga[]) {
    char fermata[STR];
    sscanf(riga," %s", fermata);
    int i;

    printf("Elenco di tutte le corse che fanno capolinea alla fermata %s\n", fermata);
    // etichette stampa
    printf("%-10s %-15s %-15s %-12s %-13s %-13s %-8s\n","Codice", "Partenza", "Destinazione", "Data", "Ora Part.", "Ora Arr.", "Ritardo");
    printf("-------------------------------------------------------------------------------------------\n");

    for (i=0; i<tab.n_voci; i++){
        if (!strcmp(fermata, tab.log[i].destinazione)){
            stampaVoce(tab.log[i]);
        }
    }
}

void partenze(tabella_t tab, char riga[]){
    char fermata[STR];
    sscanf(riga," %s", fermata);
    int i;

    printf("Elenco di tutti le corse partite dalla fermata %s\n", fermata);
    // etichette stampa
    printf("%-10s %-15s %-15s %-12s %-13s %-13s %-8s\n","Codice", "Partenza", "Destinazione", "Data", "Ora Part.", "Ora Arr.", "Ritardo");
    printf("-------------------------------------------------------------------------------------------\n");

    for (i=0; i<tab.n_voci; i++){
        if (!strcmp(fermata, tab.log[i].partenza)){
            stampaVoce(tab.log[i]);
        }
    }
}

void date(tabella_t tab, char riga[]){
    data_t data_start, data_end;
    int i;
    if (sscanf (riga,"%d/%d/%d %d/%d/%d", &data_start.aa, &data_start.mm, &data_start.gg, &data_end.aa, &data_end.mm, &data_end.gg)!=6){
        perror("Formato date errato");
        exit(-1);
    }
    printf("Elenco di tutte le corse partite tra il %04d/%02d/%02d e il %04d/%02d/%02d\n", data_start.aa, data_start.mm, data_start.gg, data_end.aa, data_end.mm, data_end.gg);

    // etichette stampa
    printf("%-10s %-15s %-15s %-12s %-13s %-13s %-8s\n","Codice", "Partenza", "Destinazione", "Data", "Ora Part.", "Ora Arr.", "Ritardo");
    printf("-------------------------------------------------------------------------------------------\n");

    for (i=0; i<tab.n_voci; i++){
        //Controllo data_start<data_record
        if (confrontaDate(data_start,data_end)){
            perror("Range date invalido");
            exit(-1);
        }
        if (confrontaDate(tab.log[i].data, data_start) && confrontaDate(data_end, tab.log[i].data)){
            stampaVoce(tab.log[i]);
        }
    }
}

void stampaVoce(voce_t record) {
    printf("%-10s %-15s %-15s %04d/%02d/%02d   %02d:%02d:%02d      %02d:%02d:%02d      %-8d\n",
           record.codice,
           record.partenza,
           record.destinazione,
           record.data.aa, record.data.mm, record.data.gg,
           record.p.h, record.p.m, record.p.s,
           record.d.h, record.d.m, record.d.s,
           record.ritardo);
}

int confrontaDate(data_t data1, data_t data2){
    if (data1.aa > data2.aa) {
        return 1;
    } else if (data1.aa < data2.aa) {
        return 0;
    } else {  // gli anni sono uguali
        if (data1.mm > data2.mm) {
            return 1;
        } else if (data1.mm < data2.mm) {
            return 0;
        } else {  // i mesi sono uguali
            if (data1.gg > data2.gg) {
                return 1;
            } else {
                return 0;
            }
        }
    }
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

    printf("\nMenu:\n- date [data_inizio] [data_fine] \n- partenza [nome_fermata] \n- capolinea [nome_fermata] \n- ritardo [data_inizio] [data_fine]\n- ritardo_tot [codice_tratta] \n- fine\ncomando: ");
    scanf("%s",comando); // read only cmd
    strToLower(comando);
    cmd = r_date;
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
