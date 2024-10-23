#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUTFILE_PATH "mat.txt"

void separa(int **mat, int nr, int nc, int** b, int** w);
int **malloc2dR(int nr, int nc);
void malloc2dP(int ***mp, int nr, int nc);
void stampaMat(int **m, int nr, int nc);
void free2d(int **m, int nr);

int main(int argc, char ** argv){
    int nr, nc, **matR, **matP, *black, *white;

    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fscanf(fp, "%d %d ", &nr, &nc);
    //printf("%d %d \n", nr, nc);

    matR = malloc2dR(nr,nc);
    malloc2dP(&matP,nr,nc);

    // leggi matrice
    int i,j, val;
    for(i=0;i<nr;i++) {
        for (j = 0; j < nc; j++) {
            fscanf(fp, "%d ", &val);
            matR[i][j] = val;
            matP[i][j] = val;
            //printf("%d %d\n", val, matP[i][j]);
        }
        fscanf(fp, "\n");
        //printf("\n");
    }

    //stampaMat(matR, nr, nc);
    //stampaMat(matP,nr,nc);
    separa(matP,nr,nc, &black, &white);

    // dealloca le matrici
    free2d(matP,nr);

    //stampa vettori
    int len_black = (nr*nc)/2;
    int len_white = (nr*nc)-len_black;

    printf("Vettore bianchi:\n");
    for(j=0; j<len_white;j++){
        printf("%d ", white[j]);
    }
    printf("\nVettore neri:\n");
    for(j=0; j<len_black;j++){
        printf("%d ", black[j]);
    }
    free(black);
    free(white);

    fclose(fp);
    return 0;
}

void free2d(int **m, int nr) {
    int i;
    for(i=0; i<nr;i++){
        free(m[i]);
    }
    free(m);
}

void separa(int **mat, int nr, int nc, int** b, int** w){
    int i,j, nb = (nr*nc)/2, nw = (nr*nc)-nb, ib,iw;
    *b = malloc(nb*sizeof(int));
    *w = malloc(nw*sizeof(int));

    ib=0;iw=0;
    // scorre la matrice finchè i vettori b (black) e w(white) sono completamente pieni
        for (i=0;i<nr;i++){
            for(j=0; j<nc;j++){
                if((i+j)%2==0){       // i+j pari -> bianco
                    (*w)[iw] = mat[i][j];
                    iw++;
                }else{              // i+j dispari -> nero
                    (*b)[ib] = mat[i][j];
                    ib++;
                }
                //printf("%d %d \n", iw, ib);
            }
        }

}

void stampaMat(int **m, int nr, int nc){
    int i,j;
    // Stampa
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
}

int **malloc2dR(int nr, int nc){
    int i, **m;
    m = malloc(nr*sizeof(int*));
    for (i = 0; i<nr; i++){
        m[i] = malloc(nc*sizeof (int));
    }
    return m;
}

void malloc2dP(int ***mp, int nr, int nc){
    int i,j,**m;
    m = malloc(nr*sizeof (int*));
    for (i=0; i<nr;i++){
        m[i] = malloc(nc*sizeof(int));
    }
    *mp = m;
}