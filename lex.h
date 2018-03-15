#ifndef LEXX_H_INCLUDED
#define LEXX_H_INCLUDED

#include "jeton.h"
//Transformation d'une chaine de caract�re en tableau de lexem
void lex(char str[], typeToken t[]);

//Retirer les espaces
void removeWhiteSpaces(char chaine[], char copy[]);

//Convertir le tableau de char(int) en int [Exemple [1][2][3] -> 123]
int charToInt(char test[]);

#endif // LEXX_H_INCLUDED
