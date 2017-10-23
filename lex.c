#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lex.h"

int lex(char str[], typeToken t[]){
    int i=0, j= 0;
    while(str[i] != '\0'){
        switch(tolower(str[i])){

            case '+' : t[j].lexem = OPERATOR;
                t[j].valor.ope = PLUS;
                break;

            case '-' : t[j].lexem = OPERATOR;
                t[j].valor.ope = MINUS;
                break;

            case '*' : t[j].lexem = OPERATOR;
                t[j].valor.ope = MULTIP;
                break;

            case '/' : t[j].lexem = OPERATOR;
                t[j].valor.ope = DIV;
                break;

            case '^' : t[j].lexem = OPERATOR;
                t[j].valor.ope = POW;
                break;

            case '(' : t[j].lexem = PAR_OP;
                break;

            case ')' : t[j].lexem = PAR_CL;
                break;

            case 'x' : t[j].lexem = VAR;
            break;

            default :
                if((str[i]<'a') && (str[i]>'z')){
                    //erreur
                }
                if((str[i]<'0') && (str[i]>'9')){
                    //erreur
                }
                else {
                    //Error
                }
                break;
        }
        i++;
        j++;
    }
    t[j].lexem = END;
    t[j].valor.err.code = 100;
    sprintf(t[j].valor.err.message, "Success");
    return 0;
}

