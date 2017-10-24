#include <stdio.h>
#include <stdlib.h>

#include "lex.h"

int main(){
    char str[20];
    char cpy[20];
    gets(str);
    /*typeToken tab[20];
    lex(str, tab);
    int i;
    for(i = 0;i <= 15; i++){
        printf("%d\n", tab[i].lexem);
    }*/
    retirer_caracteres_blancs(str, cpy);
    printf("%c%c%c\n", cpy[0], cpy[1], cpy[2]);
    return 0;
}
