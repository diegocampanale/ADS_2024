#include <stdio.h>

#define INPUTFILE_PATH "./corse.txt"

int gcd(int a, int b);

int main(int argc, char ** argv){

    printf("gcd: %d",gcd(600,54));
}

int gcd(int a, int b){

    if (a<b){
        int temp = b;
        b = a;
        a = temp;
    }

    if (b==0) return a;
    if (b==1) return 1;

    if ((a%2 == 0) && (b%2==0)){ // a,b even
        return 2*gcd(a/2, b/2);
    }
    if (a%2==0 && b%2) { // a even, b odd
        return gcd(a/2, b);
    }
    if (a%2 && b%2==0) { // a odd, b even
        return gcd(a, b/2);
    }
    if (a%2 && b%2) { // a,b odd
        return gcd((a-b)/2, b);
    }
}