#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lex.h"

void lex(char str[], typeToken t[]){
    //i avance dans la saisie user, j dans le tableau typeToken
    //errors compte les erreurs, occurence compte les occurences avec les fonctions
    int i = 0, j = 0, errors = 0, occurence = 0;

    char functions[][6] = {
        "SIN",
        "COS",
        "TAN",
        "SQRT",
        "ABS",
        "LOG",
        "EXP",
        "INT",
        "VALNE",
        "SINC"
    };

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
            int ind = 0, k;
            char tmp[20] = {};
            while(isalpha(str[i])){
                tmp[ind] = toupper(str[i]);
                ind++;
                i++;
            }
            i--;


            for(k = 0; k < 10; k++){ // verification des nom des fonctions
                if(strcmp(functions[k], tmp) == 0){
                    t[j].lexem = FUNCT;
                    t[j].valor.funct = k;
                    occurence++;
                    break;
                }
            }

            if(occurence <= 0){
                t[j].lexem = ERROR;
                t[j].valor.err.code = 102;
                sprintf(t[j].valor.err.message, "Chaine non reconnue\n");
                printf("Chaine non reconnue\n");
                errors++;
            }
        }

        else if((str[i]>='0') && (str[i]<='9')){
            int ind = 0;
            char tmp[20];
            while(isdigit(str[i]) != 0 || str[i] == '.'){
                tmp[ind] = str[i];
                ind++;
                i++;
            }
            i--;

            //Besoin d'un pointeur pour convertir le tableau de reel a virgules en un reel
            char* pt;
            t[j].lexem = REAL;
            t[j].valor.real = strtod(tmp, &pt);
        }

        else{
            t[j].lexem = ERROR;
            t[j].valor.err.code = 101;
            sprintf(t[j].valor.err.message, "Caractere non reconnu\n");
            printf("Caractere non reconnu\n");
            errors++;
            break;
        }

        if(errors > 0){
            break;
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

