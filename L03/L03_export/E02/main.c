#include <stdio.h>

#define INPUTFILE_PATH "brani.txt"

int main(int argc, char ** argv){
    char buf[100];
    FILE *fp = fopen(INPUTFILE_PATH, "r");
    fgets(buf, 100,fp);

    printf("Hello Template 2!\n");
    printf("%s", buf);

    return 0;
}
