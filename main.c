#include <stdlib.h>
#include <stdio.h>

//#include "eval.h"
#include "graph.h"
//#include "lex.h"

int main(int argc, char **argv)
{
	//typeToken t[18];

	char str[20] = {'\0'};

    //Tableau copie pour enlever les espaces
    char cpy[20] = {'\0'};

    //Tableau a transmettre
    typeToken t[20] = {};

    //Saisie utilisateur & retrait des espaces
    gets(str);

    //Retrait des espaces
    removeWhiteSpaces(str, cpy);

    //Definition des lexems
    lex(cpy, t);


	/*t[0].lexem = PAR_OP;
	t[0].value.real = 0;

	t[1].lexem = REAL;
	t[1].value.real = 2;

	t[2].lexem = PAR_CL;
	t[2].value.real = 0;

	t[3].lexem = OPERATOR;
	t[3].value.ope = PLUS;

	t[4].lexem = FUNCT;
	t[4].value.funct = SIN;

	t[5].lexem = PAR_OP;
	t[5].value.real = 0;

	t[6].lexem = REAL;
	t[6].value.real = 3;

	t[7].lexem = OPERATOR;
	t[7].value.ope = PLUS;

	t[8].lexem = PAR_OP;
	t[8].value.real = 0;

	t[9].lexem = FUNCT;
	t[9].value.funct = COS;

	t[10].lexem = PAR_OP;
	t[10].value.real = 0;

	t[11].lexem = VAR;
	t[11].value.real = 0;

	t[12].lexem = OPERATOR;
	t[12].value.ope = MULTIP;

	t[13].lexem = REAL;
	t[13].value.real = 6;

	t[14].lexem = PAR_CL;
	t[14].value.real = 0;

	t[15].lexem = PAR_CL;
	t[15].value.real = 0;

	t[16].lexem = PAR_CL;
	t[16].value.real = 0;

	t[17].lexem = END;
	t[17].value.real = 0;*/

	int y = 0;

	int * i = &y;

	Tree arbre = Synt(t, i);

	//printf("Arbre: %d", arbre->pTokNext->tok.lexem);

	//printf("Premier Lexem : %d\n", arbre->tok.lexem);

	// Après le Synt(), l'arbre est mal situé

    	Result res = Eval(&arbre,-7.5);

	printf("f(-7.5) = %f",res.value);

    printf("JARRIVE");
    tracer(&arbre);


	free(arbre);

	return 0;
}
