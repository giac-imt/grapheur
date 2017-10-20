#include <stdio.h>
#include <stdlib.h>

#include <lex.h>
#include <jeton.h>

#include <lex.c>

int main()
{
    printf("Hello world!\n");
    return 0;

    char str[20];
    gets(str);
    typeToken tab[20];
    int e;
    e = lex(str, tab);
}
