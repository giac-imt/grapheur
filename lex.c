#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lex.h"

int lex(char str[], typeToken t[]){
    //i avance dans la saisie user, j dans le tableau typeToken
    int i=0, j= 0;

    //Différencier la barre ouvrante de la barre fermante
    int barre = 0;

    while(str[i] != '\0'){
        switch(str[i]){

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

            case '|' :
                if(barre == 0){
                    t[j].lexem = BAR_OP;
                    barre = 1;
                } else {
                    t[j].lexem = BAR_CL;
                    barre = 0;
                }
                break;

            case 'x' :
                t[j].lexem = VAR;
                break;

            default :
                if((str[i]>'a') && (str[i]<'z')){
                    //Impossible de rentrer dans ce if
                    printf("Alphabet\n");
                }
                if((str[i]>'0') && (str[i]<'9')){
                    //Ni dans celui-là
                }
                else {
                    t[j].lexem = ERROR;
                    t[j].valor.err.code = 101;
                    sprintf(t[j].valor.err.message, "Aucune correspondance trouvée\n");
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

