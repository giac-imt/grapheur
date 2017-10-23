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

    float res;
    typeError err;
    err.code = 300;
    strcpy(err.message,"");

    if(tree != NULL)
    {
        typeToken token = (*tree)->tok;
        Tree fPrev = (*tree)->pTokBfor;
        Tree fNext = (*tree)->pTokNext;

        switch(token.lexem)
        {
        case REAL:
            res = token.value.real;
            break;

        case OPERATOR:
            ;
            Result tmpPrev = Eval(&fPrev, x);
            Result tmpNext = Eval(&fNext, x);
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
            tmpPrev = Eval(&fPrev, x);
            tmpNext = Eval(&fNext, x);
            if(tmpPrev.err.code == 300  && tmpNext.err.code == 300)
            {
                switch(token.value.funct)
                {
                case SIN:
                    res = sinf(token.value.real);
                    break;

                case COS:
                    res = cosf(token.value.real);
                    break;

                case TAN:
                    res = tanf(token.value.real);
                    break;

                case SQRT:
                    res = sqrtf(token.value.real);
                    break;

                case ABS:
                    if(token.value.real < 0)
                        res = - token.value.real;
                    else
                        res = token.value.real;
                    break;

                case LOG:
                    res = logf(token.value.real);
                    break;

                case EXP:
                    res = expf(token.value.real);
                    break;

                case INT:
                    res = (float)(int)token.value.real;
                    break;

                case VAL_NEG:
                    res = - token.value.real;
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
    }
    else
    {
        err.code = 301;
        sprintf(err.message,"Null token");
    }

    Result ret;
    ret.value = res;
    ret.err = err;
    return ret;
}
