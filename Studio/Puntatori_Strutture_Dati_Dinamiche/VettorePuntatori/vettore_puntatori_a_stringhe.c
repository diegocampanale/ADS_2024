#include <stdio.h>
#include <string.h>

void ordinaMatrice(char pString[20][51], int ns);

int main(void) {
    int i, ns;
    char *v[20], buf[520];
    printf("Scrivi stringhe:\n");
    for(ns=i=0; ns<20; ns++){
        v[ns]=buf+i;
        gets(v[ns]);
        if(strlen(v[ns])==0)
            break;
        i=i+strlen(v[ns])+1;
    }
    printf("Stringhe ordinate:\n");
    for(i=0; i<ns; i++){
        printf("%s\n",v[i]);
    }

    printf("v: %d byte\n",sizeof(v));
    printf("buf: %d byte\n",sizeof(buf));


    /*
    char m[20][51]; // 20 n_max stringhe, 51 len_max stringa
    printf("Scrivi stringhe:\n");
    for(ns=0; ns<20; ns++){
        fgets(m[ns],51,stdin);

        // Rimuove il carattere newline ('\n') se presente
        if (m[ns][strlen(m[ns]) - 1] == '\n') {
            m[ns][strlen(m[ns]) - 1] = '\0';
        }
        if(strlen(m[ns])==0) break;
    }
    ordinaMatrice(m,ns);
    printf("Stringhe ordinate:\n");
    for(i=0; i<ns; i++){
        printf("%s\n",m[i]);
    }
     */

    return 0;
}

void ordinaMatrice(char pString[20][51], int ns) {

}
