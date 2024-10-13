#include <stdio.h>

#define INPUTFILE_PATH "./out.txt"

int main(int argc, char ** argv){
    char buf[100];
    FILE *fp = fopen(INPUTFILE_PATH, "w");

    //fgets(buf, 100,fp);

    printf("Hello Template!\n");
    fprintf(fp,"CIao");

    return 0;
}
