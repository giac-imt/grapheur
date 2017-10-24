#include <stdlib.h>
#include <stdio.h>

#include "Syntaxe.h"

int main()
{
	typeToken t[18];
	
	
	t[0].lexem = PAR_OP;
	t[0].valor.real = 0;
	
	t[1].lexem = REAL;
	t[1].valor.real = 2;
	
	t[2].lexem = PAR_CL;
	t[2].valor.real = 0;
	
	t[3].lexem = OPERATOR;
	t[3].valor.ope = PLUS;
	
	t[4].lexem = FUNCT;
	t[4].valor.funct = SIN;
	
	t[5].lexem = PAR_OP;
	t[5].valor.real = 0;
	
	t[6].lexem = REAL;
	t[6].valor.real = 3;
	
	t[7].lexem = OPERATOR;
	t[7].valor.ope = PLUS;
	
	t[8].lexem = PAR_OP;
	t[8].valor.real = 0;
	
	t[9].lexem = FUNCT;
	t[9].valor.funct = COS;
	
	t[10].lexem = PAR_OP;
	t[10].valor.real = 0;
	
	t[11].lexem = VAR;
	t[11].valor.real = 0;
	
	t[12].lexem = PAR_CL;
	t[12].valor.real = 0;
	
	t[13].lexem = OPERATOR;
	t[13].valor.ope = MULTIP;
	
	t[14].lexem = REAL;
	t[14].valor.real = 6;
	
	t[15].lexem = PAR_CL;
	t[15].valor.real = 0;
	
	t[16].lexem = PAR_CL;
	t[16].valor.real = 0;
	
	t[17].lexem = END;
	t[17].valor.real = 0;
	
	int y = 0;
	
	int * i = &y;
	
	Tree arbre = Synt(t, i);

	return 0;
}
