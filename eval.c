#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "eval.h"

Result eval(Tree *tree, float x)
{
    typeToken token = (*tree)->tok;
    Tree fPrev = (*tree)->pTokBfor;
    Tree fNext = (*tree)->pTokNext;

    float res;

    switch(token.lexem)
    {
    case REAL:
        res = token.value.real;
        break;

    case OPERATOR: ;
        Result tmpPrev = eval(fPrev, x);
        Result tmpNext = eval(fNext, x);

        switch(token.value.ope)
            {
            case PLUS:
                res = tmpPrev.value + tmpNext.value;
                break;

            case MINUS:
                res = tmpPrev.value - tmpNext.value;
                break;

            case MULTIP:
                res = tmpPrev.value * tmpNext.value;
                break;

            case DIV:
                res = tmpPrev.value / tmpNext.value;
                //ATTENTION DIIVISION PAR 0
                break;

            case POW:
                res = powf(tmpPrev.value,tmpNext.value);
                break;
            }
        break;

    case FUNCT:
        switch(token.value.funct)
            {
            case SIN:
                break;

            case COS:
                break;

            case TAN:
                break;

            case SQRT:
                break;

            case ABS:
                break;

            case LOG:
                break;

            case EXP:
                break;

            case INT:
                break;

            case VAL_NEG:
                break;

            case SINC:
                break;
            }
        break;

    case ERROR:

        break;

    case VAR:

        break;

    default:
        //Sortir une erreur
        break;
    }
}
