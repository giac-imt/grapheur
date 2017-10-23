#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "eval.h"

/** ERROR CODES
300 : no error
310 : division by 0
311 : invalid OPERATOR
**/
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
                if(tmpNext.value != 0)
                {
                    res = tmpPrev.value / tmpNext.value;
                }
                else
                {
                    res = 0;
                    err.code = 310;
                }
                break;

            case POW:
                res = powf(tmpPrev.value,tmpNext.value);
                break;
            default:
                res = 0;
                err.code = 311;
                sprintf(err.message, "Invalid OPERATOR : %d", token.value.ope);
                break;
            }
        }
        else
        {
            if(tmpPrev.err.code != 300)
            {
                err = tmpPrev.err;
            }
            else
            {
                err = tmpNext.err;
            }
        }
        break;

    case FUNCT:
        ;
        tmpPrev = eval(&fPrev, x);
        tmpNext = eval(&fNext, x);
        if(tmpPrev.err.code == 300  && tmpNext.err.code == 300)
        {
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
        }
        else
        {
            if(tmpPrev.err.code != 300)
            {
                err = tmpPrev.err;
            }
            else
            {
                err = tmpNext.err;
            }
        }
        break;

    case ERROR:
        err = token.value.err;
        break;

    case VAR:
        res = x;
        break;

    default:
        err.code = 312;
        sprintf(err.message, "invalid Lexem");
        break;
    }

    Result ret;
    ret.value = res;
    ret.err = err;
    return ret;
}
