#include <stdio.h>
#include <stdlib.h>

#include "lex.h"

int main(){
    char str[20];
    gets(str);
    typeToken tab[20];
    lex(str, tab);
    int i;
    for(i = 0;i <= 4; i++){
        printf("%d\n", tab[i].lexem);
    }
    return 0;
}
