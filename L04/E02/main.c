#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUTFILE_PATH "anag1.txt"
#define OUTFILE_PATH "out.txt"
#define MAXS 50

typedef enum {r_add, r_search, r_extract, r_print, r_exit} comando_e;
typedef struct { int g; int m; int a; } data_t;
typedef struct{
    char codice[MAXS];
    char nome[MAXS];
    char cognome[MAXS];
    char data_str[11];
    data_t data;
    char via[MAXS];
    char citta[MAXS];
    int cap;
}Item;

typedef struct node{
    Item val;
    struct node *next;
}node_t, *link;

void printMenu(void);
int printListR(link h,FILE* fout);
int printNode(Item val,FILE* fout);
void strToLower(char *str);
comando_e readCmd(char comandi[][MAXS]);
void opt_print(link head);
link opt_add(link head,char *buf);
link readFileIns(link head,FILE* fp);
int confrontaDate(data_t data1, data_t data2);
link newNode(Item val, link next);
link SortListIns(link h,Item val);
Item searchByCode(link h, char *key);
void opt_search(link head,char *buf);
Item ITEMsetvoid();
int isFormatCode(char *cod);
int isItemVoid(Item item);
void opt_extract(link head, char *buf);
Item listExtrKeyP(link *hp,char *key);
int isValidReadData(char *date_str, data_t *data1p, data_t *data2p);


int main(int argc, char ** argv){
    // Dichiarazione variabili
    char comandi[][MAXS] = {"add","search","extract","print","exit" };
    comando_e cmd;
    int uscita = 0;
    char buf[MAXS];

    // inizializzazione lista vuota
    link head=NULL;

    // menu e acquisizione comando
    while (uscita==0){
        printMenu();
        cmd = readCmd(comandi);
        fgets(buf,MAXS,stdin); // lettura resto della riga
        sscanf(buf," %99[^\n]",buf); //rimozione spazio iniziale
        // printf("cmd: %d %s%s\n", cmd, comandi[cmd],buf); // debug

        switch (cmd) {
            case r_add:
                head = opt_add(head,buf);
                break;
            case r_search:
                opt_search(head,buf);
                break;
            case r_extract:
                opt_extract(head,buf);
                break;
            case r_print:
                opt_print(head);
                break;
            case r_exit:
                uscita=1;
                break;
            default:
                printf("Errore comando!\n");
        }
    }
    return 0;
}

// Funzioni switch //
void opt_extract(link head, char *buf){

    if(isFormatCode(buf)){ // Caso inserimento codice
        Item extract = listExtrKeyP(&head,buf);
        if(isItemVoid(extract)) {
            printf("Elemento non trovato!\n");
        }else{
            printf("Elemento rimosso:\n");
            printNode(extract,stdout);
        }
    }/*else{ // Caso inserimento data range
        data_t data_start, data_end;
        if(isValidReadData(buf,&data_start,&data_end)){
            link extractList=NULL;
            while (extractList!=NULL){

            }
        }else{ // Caso inserimento errato

        }
    }*/
}
void opt_search(link head,char *buf){
    Item record;
    record = searchByCode(head,buf);
    if(isItemVoid(record))
        printf("Elemento non trovato!\n");
    else
        printNode(record,stdout);

}
link opt_add(link head,char *buf){
    if(buf[1]=='f'){ // opzione file
        sscanf(buf,"-f %s", buf);

        FILE *fin = fopen(buf, "r");
        if(fin == NULL){
            printf("Errore apertura file!\n");
            exit(-1);
        }
        head = readFileIns(head,fin);
        fclose(fin);
    }else{ // opzione keyboard
        head = readFileIns(head,stdin);
    }
    return head;
}
void opt_print(link head){
    FILE *fout;
    int result;
    if ((fout = fopen("ciao.txt", "w")) == NULL) {
        perror("Errore apertura file!");
        exit(-1);
    }
    fprintf(fout, "Test");
    result = printListR(head,fout); //   NON STAMPA SU out.txt //
    // result = printListR(head,stdout); // debug
    fclose(fout);

    if (result > 0){
        printf("Stampa su file %s eseguita con successo!\n",OUTFILE_PATH);
    }else{
        printf("Nessun elemento da stampare\n");
    }
}

// Funzioni ausiliarie //
int isValidReadData(char *date_str, data_t *data1p, data_t *data2p){
    int matched = sscanf(date_str, "%d/%d/%d %d/%d/%d",&data1p->g,&data1p->m,&data1p->a,&data2p->g,&data2p->m,&data2p->a);
    if(matched==6 && confrontaDate(*data1p,*data2p)<=0){
        return 1;
    }
    return 0;
}
Item listExtrKeyP(link *hp,char *key){
    link *xp, t;
    Item i = ITEMsetvoid();
    for(xp=hp; (*xp)!= NULL ; xp = &((*xp)->next) ){
        if(strcmp(key,(*xp)->val.codice)==0){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}
int isFormatCode(char *cod){
    int i, valid = 1;
    if(cod[0] == 'A'){
        for (i=1; i<5; i++) {
            if (isdigit(cod[i]) == 0) {
                valid = 0;
            }
        }
        return valid;
    }
    return 0;
}
int isItemVoid(Item item){
    if(strcmp(item.codice,"")==0)
        return 1;
    return 0;
}
Item ITEMsetvoid(){
    Item item_void;
    strcpy(item_void.codice,"");
    strcpy(item_void.nome,"");
    strcpy(item_void.cognome,"");
    strcpy(item_void.data_str,"");
    item_void.data.g = 0;
    item_void.data.m = 0;
    item_void.data.a = 0;
    strcpy(item_void.via,"");
    strcpy(item_void.citta,"");
    item_void.cap = 0;

    return item_void;
}
Item searchByCode(link h, char *key){
    link x;
    for(x=h; x!=NULL; x=x->next){       // Ricerca di una chiave in lista non ordinata (per codice)
        if(strcmp(x->val.codice,key)==0){
            return x->val;
        }
    }
    return ITEMsetvoid();
}
link readFileIns(link head,FILE* fp){
    Item record;
    if (fp == stdin){
        printf("Inserimento record anagrafica\n");
        printf("codice: "); scanf(" %s",record.codice);
        printf("nome: "); scanf(" %s",record.nome);
        printf("cognome: "); scanf(" %s",record.cognome);
        printf("data di nascita <gg/mm/aaaa>: "); scanf(" %s",record.data_str);
        sscanf (record.data_str,"%d/%d/%d", &record.data.g,&record.data.m,&record.data.a);
        printf("via: "); scanf(" %s",record.via);
        printf("città: "); scanf(" %s",record.citta);
        printf("cap: "); scanf(" %d",&record.cap);

        head = SortListIns(head,record);
    }else{
        while(fscanf(fp,"%s %s %s %s %s %s %d\n",record.codice, record.nome, record.cognome, record.data_str, record.via, record.citta, &record.cap) != EOF){
            sscanf (record.data_str,"%d/%d/%d", &record.data.g,&record.data.m,&record.data.a);
            head = SortListIns(head,record);
        }
    }
    return head;
}
link SortListIns(link h,Item val){
    link x, p;
    data_t key = val.data;

    // inserimento in testa //
    if(h==NULL || confrontaDate(h->val.data,key)>0)
        return newNode(val,h);

    // cerca posizione
    for(x=h->next, p=h; x!= NULL && confrontaDate(x->val.data,key)<0; p=x, x=x->next);
    if(p->next == NULL || strcmp(p->next->val.codice,val.codice)!=0)
        p->next = newNode(val,x);
    return h;
}
link newNode(Item val, link next){
    link x= malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}
int confrontaDate(data_t data1, data_t data2){
    if (data1.a > data2.a) {
        return 1;
    } else if (data1.a < data2.a) {
        return -1;
    } else {  // gli anni sono uguali
        if (data1.m > data2.m) {
            return 1;
        } else if (data1.m < data2.m) {
            return -1;
        } else {  // i mesi sono uguali
            if (data1.g > data2.g) {
                return 1;
            } else if (data1.g < data2.g){
                return -1;
            } else{ // i giorni sono uguali
                return 0;
            }
        }
    }
}
comando_e readCmd(char comandi[][MAXS]){
    comando_e cmd;
    char riga[100], buf[MAXS];

    scanf("%s",buf);
    strToLower(buf);
    cmd = 0;
    while(cmd<=r_exit && strcmp(buf,comandi[cmd])!=0) {
        cmd++;
    }
    return cmd;
}
void printMenu(void){
    printf("\nComandi:\n");
    printf("- add [-f nomefile] (se da file)\n");
    printf("- search [codice]\n");
    printf("- extract [codice] or [data_inizio] [data_fine]\n");
    printf("- print\n");
    printf("- exit\n");
    printf(">> ");
}
int printListR(link h,FILE* fout){
    int cnt=0;
    if(h==NULL)
        return 0;
    fprintf(fout, "Test2");

    cnt = printNode(h->val,fout);
    printListR(h->next,fout);
    return cnt;
}
int printNode(Item val,FILE* fout){
    fprintf(fout, "Test3");

    return fprintf(fout,"%-15s %-15s %-15s %02d/%02d/%04d      %-20s %-15s     %05d\n",
           val.codice,
           val.nome,
           val.cognome,
           val.data.g,val.data.m,val.data.a,
           val.via,
           val.citta,
           val.cap
    );
}
void strToLower(char *str) {
    int size = strlen(str);
    for (int i = 0; i<size; i++){
        str[i] = tolower(str[i]);
    }
    return;
}

