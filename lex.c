#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lex.h"

void lex(char str[], typeToken t[]){
    //i avance dans la saisie user, j dans le tableau typeToken
    int i = 0, j = 0;

    while(str[i] != '\0'){
        if(str[i] == '+'){
            t[j].lexem = OPERATOR;
            t[j].valor.ope = PLUS;
        }

        else if(str[i] == '-'){
            t[j].lexem = OPERATOR;
            t[j].valor.ope = MINUS;
        }

        else if(str[i] == '*'){
            t[j].lexem = OPERATOR;
            t[j].valor.ope = MULTIP;
        }

        else if(str[i] == '/'){
            t[j].lexem = OPERATOR;
            t[j].valor.ope = DIV;
        }

        else if(str[i] == '^'){
            t[j].lexem = OPERATOR;
            t[j].valor.ope = POW;
        }

        else if(str[i] == '('){
            t[j].lexem = PAR_OP;
        }

        else if(str[i] == ')'){
            t[j].lexem = PAR_CL;
        }

        else if(str[i] == '['){
            t[j].lexem = BAR_OP;
        }

        else if(str[i] == ']'){
            t[j].lexem = BAR_CL;
        }

        else if(str[i] == 'x'){
            t[j].lexem = VAR;
        }

        else if(((str[i]>='a') && (str[i]<='z')) || ((str[i]>='A') && (str[i]<='Z'))){
            t[j].lexem = FUNCT;
        }

        else if((str[i]>='0') && (str[i]<='9')){
            int ind = 0;
            char tmp[20];
            while(isdigit(str[i]) != 0){
                tmp[ind] = str[i];
                ind++;
                i++;
            }
            i--;
            t[j].lexem = REAL;
            t[j].valor.real = atoi(tmp);
            printf("%d\n", atoi(tmp));
        }

        else{
            t[j].lexem = ERROR;
            t[j].valor.err.code = 101;
            sprintf(t[j].valor.err.message, "Charactere non reconnu\n");
        }
        i++;
        j++;
    }
    t[j].lexem = END;
    t[j].valor.err.code = 100;
    sprintf(t[j].valor.err.message, "Success\n");
}

void removeWhiteSpaces(char chaine[], char copy[]){
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

int charToInt(char test[]){
    int i = 0;
    int result = 0;
    int len = strlen(test);
    for(i=0; i<len; i++){
        result = result * 10 + ( test[i] - '0' );
    }
    return result;
}
