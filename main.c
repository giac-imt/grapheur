#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lex.h"

int main(){
    //Tableau de saisie
    char str[20] = {'\0'};

    //Tableau copie pour enlever les espaces
    char cpy[20] = {'\0'};

    //Tableau a transmettre
    typeToken tab[20] = {};

    //Saisie utilisateur & retrait des espaces
    gets(str);

    //Retrait des espaces
    removeWhiteSpaces(str, cpy);

    //Definition des lexems
    lex(cpy, tab);

    int i;

    for(i = 0; i < 10; i++){
        printf("%d\n", tab[i]);
    }

    return 0;
}
