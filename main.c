#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lex.h"

int main(){
    //Tableau de saisie
    char str[20];

    //Tableau copié pour enlever les espaces
    char cpy[20];

    //Tableau à transmettre
    typeToken tab[20];

    //Saisie utilisateur & retrait des espaces
    gets(str);
    removeWhiteSpaces(str, cpy);

    //Définition des lexems
    //lex(cpy, tab);

    //DEBUG : Affichage des lexems
    int i;
    for(i = 0;i <= 3; i++){
        printf("%d\n", tab[i].lexem);
    }/*
    int i = 0;
    char tmp[20];
    while(str[i] != '\0'){
        int ind = 0;
        while(isdigit(str[i]) != 0){
            tmp[ind] = str[i];
            ind++;
            i++;
        }
    }

    tmp[i] = '\0';

    printf("%s\n", tmp);*/
    return 0;
}
