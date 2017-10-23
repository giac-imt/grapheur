#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "eval.h"

Result eval(Tree *tree, float x)
{
    typeToken token = (*tree)->tok;
    Tree fPrev = (*tree)->pTokBfor;
    Tree fNext = (*tree)->pTokNext;

    float res;
    typeError err;
    err.code = 300;
    strcpy(err.message,"");

    switch(token.lexem)
    {
    case REAL:
        res = token.value.real;
        break;

    case OPERATOR:
        ;
        Result tmpPrev = eval(&fPrev, x);
        Result tmpNext = eval(&fNext, x);
        if(tmpPrev.err.code == 300  && tmpNext.err.code == 300)
        {
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

    Result ret;
    ret.value = res;
    ret.err = err;
    return ret;
}
