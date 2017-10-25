#ifndef LEXX_H_INCLUDED
#define LEXX_H_INCLUDED

#include "jeton.h"
//Transformation d'une chaine de caractère en tableau de lexem
int lex(char str[], typeToken t[]);

//Retirer les espaces
void removeWhiteSpaces(char chaine[], char copy[]);

#endif // LEXX_H_INCLUDED
