/*#include <stdio.h>

int majority( int *a, int N);

int main(int argc, char ** argv){

    printf("Hello Template 1!\n");

    return 0;
}

int majority( int *a, int N){

}*/

#include <stdio.h>
#include <string.h>

int occorrenze(int *vet,int lungVet, int elem){
    int occ=0;
    for (int i=0;i<lungVet;i++){
        if(vet[i]==elem){occ++;}
    }
    return occ;
}

int majority(int *vet,int lungVet){
    int q, magDisinistra,magDidestra,occSin,occDest;
    if (lungVet==1){return vet[0];}
    q=lungVet/2;
    magDisinistra=majority(vet, q);
    magDidestra=majority(vet+q, lungVet-q);
    if (magDisinistra==magDidestra){return magDisinistra; // SE IL RISULTATO DI DESTRA è == A QUELLO DI SINISTRA, SARà QUELLO L'ELEMENTO MAGGIORITARIO
    } else{  // SE I RISULTATI SONO DIVERSI, SI CONTANO LE OCCORRENZE DI ENTRAMBI GLI ELEMENTI (SINISTRA E DESTRA)
        occSin=occorrenze(vet,lungVet,magDisinistra);
        occDest=occorrenze(vet+q,lungVet,magDidestra);
    }
    if (occDest<occSin){return magDisinistra;} //  SI CONFRONTANO LE OCCORRENZE, L'ELEMENTO CHE COMPARE PIU VOLTE VIENE RESTITUITO
    else{return magDidestra;}
};

int main() {
    int n,i,mag, vet[]={3, 3, 9, 4, 3, 5, 3};
    n=7;
    mag=majority(vet,n);
    i=occorrenze(vet,n,mag);
    if (i>n/2){
        printf("%d",mag);}
    else{printf("Non ci sono elementi maggioritari");}
    return 0;
}
