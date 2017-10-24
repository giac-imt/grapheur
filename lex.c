#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lex.h"

char functions[10][7] = {"ABS", "COS", "EXP", "INT", "LOG", "SIN", "SINC", "SQRT", "TAN", "VAL_NEG"};

int lex(char str[], typeToken t[]){
    //i avance dans la saisie user, j dans le tableau typeToken
    int i = 0, j = 0;

    while(str[i] != '\0'){
        switch(tolower(str[i])){

            case '+' :
                t[j].lexem = OPERATOR;
                t[j].valor.ope = PLUS;
                break;

            case '-' :
                t[j].lexem = OPERATOR;
                t[j].valor.ope = MINUS;
                break;

            case '*' :
                t[j].lexem = OPERATOR;
                t[j].valor.ope = MULTIP;
                break;

            case '/' :
                t[j].lexem = OPERATOR;
                t[j].valor.ope = DIV;
                break;

            case '^' :
                t[j].lexem = OPERATOR;
                t[j].valor.ope = POW;
                break;

            case '(' :
                t[j].lexem = PAR_OP;
                break;

            case ')' :
                t[j].lexem = PAR_CL;
                break;

                // Les BAR correspondent à des crochets
            case '[' :
                t[j].lexem = BAR_OP;
                break;

            case ']' :
                t[j].lexem = BAR_CL;
                break;

            case 'x' :
                t[j].lexem = VAR;
                break;

            default :
                if(((str[i]>'a') && (str[i]<'z')) || ((str[i]>'A') && (str[i]<'Z'))){
                    t[j].lexem = FUNCT;
// FAIRE KE RESTE DU CODE ICI T__T
                }
                else if((str[i]>'0') && (str[i]<'9')){
                    t[j].lexem = REAL;
                }
                else {
                    t[j].lexem = ERROR;
                    t[j].valor.err.code = 101;
                    sprintf(t[j].valor.err.message, "Aucune correspondance trouvee\n");
                }
                break;
        }
        i++;
        j++;
    }
    t[j].lexem = END;
    t[j].valor.err.code = 100;
    sprintf(t[j].valor.err.message, "Success\n");

    return 0;
}

void retirer_caracteres_blancs(char chaine[], char copy[]){
    int i,j = 0, lg;
    lg = strlen(chaine);
    for(i=0; i<lg; i++)
    {
        if(chaine[i] != ' ' && chaine[i] != '\t')
        {
            copy[j] = chaine[i];
            j++;
        }
    }
    copy[j] == '\0';
}
