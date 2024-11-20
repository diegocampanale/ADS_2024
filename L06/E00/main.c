#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE_PATH "val0.txt"

void solve(int *val, int n);
int solveR(int *val, int *opt, int n, int k);
int max(int n1, int n2);
void solveDP(int *val, int n);
void displaySol(int *val, int *opt, int n);

int main(int argc, char ** argv){
    int n,i,k;
    int *val;

    FILE *fp = fopen(INPUTFILE_PATH, "r");
    if(fp==NULL) {
        printf("Errore apertura file");
        exit(-1);
    }

    fscanf(fp," %d\n", &n);
    val = (int *) calloc(n+1,sizeof(int));
    for(i=1; i<n; i++){
        fscanf(fp," %d",&val[i]);
    }

    solve(val,n);
    solveDP(val,n);

    free(val);

    return 0;
}

void solve(int *val, int n){
    int *opt;
    opt = (int *) calloc((n+1),sizeof(int));
    printf("Soluzione ricorsiva:\n");
    printf("Massima popolazione coperta: %d\n", solveR(val,opt,n,n));
    free(opt);
}

int solveR(int *val, int *opt, int n, int k){
    if (k==0){
        return 0;
    }
    if (k==1){
        return val[1];
    }
    return max(solveR(val,opt,n,k-1), solveR(val,opt,n,k-1)+val[k]);
}
int max(int n1, int n2){
    if(n1>n2)
        return n1;
    return n2;
}

void solveDP(int *val, int n){
    int i, *opt;
    opt = (int *) calloc((n+1),sizeof(int));
    opt[1] = val[1];
    for(i=2;i<=n;i++){
        if(opt[i-1]>opt[i-2]+val[i]){
            opt[i] = opt[i-1];
        }else{
            opt[i] = opt[i-1]+val[i];
        }
    }

    printf("Soluzione con Programmazione Dinamica:\n");
    printf("Massima popolazione coperta: %d\n",opt[n]);
    displaySol(opt,val,n);
}

void displaySol(int *val, int *opt, int n){
    int i,j,*sol;
    sol = calloc(n,sizeof(int));
    sol[1] = 1;
    i=n;
    while (i>=2){
        printf("i = %d\n", i);
        if(opt[i] == opt[i-1]){
            sol[i] = 0;
            i--;
        }else if (opt[i] == opt[i-2]+val[i]){
            sol[i] = 1;
            sol[i-1] = 0;
            i--;
        }
        i--;
    }
    for(i=1; i<=n; i++){
        if(sol[i]){
            printf("%d ",val[i]);
        }
        printf("\n");
    }

}

