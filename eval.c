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
Result Eval(Tree *tree, float x)
{
    //Variable unique pour le retour, utiliser res
    float res;
    typeError err;
    err.code = 300;
    strcpy(err.message,"");

    if(*tree != NULL)
    {
        typeToken token = (*tree)->tok;
        Tree fPrev = (*tree)->pTokBfor;
        Tree fNext = (*tree)->pTokNext;

        Result tmpPrev = Eval(&fPrev, x);
        Result tmpNext = Eval(&fNext, x);

        printf("LEXEM : %d\n", token.lexem);

        switch(token.lexem)
        {
        case REAL:
            res = token.value.real;
            break;

        case OPERATOR:
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
                    sprintf(err.message, "Err 311 : Invalid OPERATOR : %d", token.value.ope);
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
            if(tmpPrev.err.code == 300)
            {
                switch(token.value.funct)
                {
                case SIN:
                    res = sinf(tmpPrev.value);
                    break;

                case COS:
                    res = cosf(tmpPrev.value);
                    break;

                case TAN:
                    res = tanf(tmpPrev.value);
                    break;

                case SQRT:
                    res = sqrtf(tmpPrev.value);
                    break;

                case ABS:
                    if(token.value.real < 0)
                        res = - tmpPrev.value;
                    else
                        res = tmpPrev.value;
                    break;

                case LOG:
                    res = logf(tmpPrev.value);
                    break;

                case EXP:
                    res = expf(tmpPrev.value);
                    break;

                case INT:
                    res = (float)(int)tmpPrev.value;
                    break;

                case VAL_NEG:
                    res = - tmpPrev.value;
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

                case END:

                    break;

        case ERROR:
            err = token.value.err;
            break;

        case VAR:
            res = x;
            break;

        default:
            err.code = 312;
            sprintf(err.message, "Err 312 : Invalid Lexem");
            break;
        }
    }
    else
    {
        err.code = 301;
        sprintf(err.message,"Err 301 : Null Token");
    }

    Result ret;
    ret.value = res;
    ret.err = err;
    return ret;
}
