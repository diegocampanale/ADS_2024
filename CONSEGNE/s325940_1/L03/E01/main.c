#include <stdio.h>

int majority( int *a, int N);
int majorityR( int *a, int l, int r);
int count(int *a, int l, int q, int r);


int main(int argc, char ** argv){

    int n=20, a[20] = {3, 3, 9, 4, 3, 5, 3,6,8,3,4,5,3,3,3,3,0,1,2,3};
    printf("maggioritario: %d", majority(a,n));
    return 0;
}

int majority( int *a, int N){
    int l=0, r=N-1;
    majorityR(a,l,r);
}

int majorityR( int *a, int l, int r){
        if (l>=r){
            return a[l];
        }
        int q = (l+r)/2;

        int magLeft = majorityR(a,l,q);   // sottovettore sx
        int magRight = majorityR(a,q+1,r);   // sottovettore dx

        int occMagLeft = count(a,l,r,magLeft);
        int occMagRight = count(a,l,r,magRight);

        if(occMagLeft>(r-l)/2){
            return magLeft;
        }else if (occMagRight>(r-l)/2){
            return magRight;
        }else {
            return -1;
        }
}

int count(int *a, int l, int r, int val){
    int i,occ=0;
    for (i=l; i<=r;i++) {
        if (a[i] == val){
            occ++;
        }
    }
    return occ;
}