#include <stdio.h>
#include <string.h>

#define MAXR 100

char *cercaRegexp(char *src, char *regexp);

int main(int argc, char **argv){

    char *regex = "m.to";
    char *stringa = "moto mato mito";
    char *occ = cercaRegexp(stringa, regex);
    if (occ == NULL) {
        printf("Stringa non valida!");
    }else{
        printf("%s", occ);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
        int len_src = strlen(src), len_regex = strlen(regexp);
        int i, k,j, valid=1, trovato=0;
        char *c = src,a,b;

        for (k=0; k<len_src;k++){
            for (i=0, j=k; i<len_regex && valid;i++){
                c = src+j;
                if (regexp[i] == '[') {
                    i++; // salta '['
                    if (regexp[i] == '^') {
                        i++; // salta '^'
                        while (regexp[i] != ']' && valid) {
                            a = regexp[i];
                            b = src[k];
                            if (regexp[i] == *c) { // se il carattere da non matchare, matcha
                                valid = 0;
                            }else{
                                j++;
                            }
                            i++;
                        } // salta ']'
                    }else{
                        trovato = 0;
                        while (regexp[i] != ']') {
                            a = regexp[i];
                            b = src[k];
                            if (regexp[i] == *c) { // se il carattere da matchare, matcha
                                trovato = 1;
                            }
                            i++; // carattere regex successivo
                        }
                        if(!trovato)// se tra le [] non c'è stato match -> valid 0
                            valid = 0;
                        else
                            j++;
                    }
                }else if (regexp[i] == '\\'){
                    i++; // salta '\'
                    a = regexp[i];
                    b = *c;
                    if (regexp[i] == 'A' && (*c < 'A' || *c > 'Z')){
                        valid = 0;
                    } else if (regexp[i] == 'a' && (*c < 'a' || *c > 'z')) {
                        valid = 0;
                    }else{
                        j++;
                    }
                } else if (regexp[i] == '.') {
                    j++; // '.' corrisponde a qualsiasi carattere
                } else if (regexp[i] != *c) {
                    valid = 0; // i caratteri non corrispondono
                } else {
                    j++; // avanza solo se i caratteri corrispondono
                }
            }
            if (valid) return src+k;
            valid = 1;
        }
        return  NULL;

}
