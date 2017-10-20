#include <stdlib.h>
#include <stdio.h>

#include "Syntaxe.h"

Tree creerNode(typeToken t, Tree fd, Tree fg)
{

	//printf("Je suis dans creerNode\n");
	Tree arbre = (Tree) malloc(sizeof(Node));
	
	arbre->tok = t;
	arbre->pTokBfor = fd;
	arbre->pTokNext = fg;
	
	return arbre;
}

Tree Synt(typeToken t[], int * i)
{
	Tree arbre = NULL;
	Tree tmp = NULL;
	
	while(t[*i].lexem != END)
	{
	
		printf("i vauts: %d\n", *i);
		printf("Le lexem vaut %d\n", t[*i].lexem);
		
		switch(t[*i].lexem)
		{
			//printf("Je suis dans le switch\n");
			case VAR: case REAL:
			{
				printf("Je suis dans real/var\n");
				
				arbre = creerNode(t[*i], NULL, NULL);

				break;
			}
			case FUNCT:
			{
			
				printf("Je suis dans func\n");
				*i = *i + 2;
				tmp = Synt(t, i);
				
				arbre = creerNode(t[*i], tmp, NULL);
				
				
				break;
			}
			case OPERATOR:
			{
				printf("Je suis dans operator\n");
				
				int * tmp_var = i;
				
				*tmp_var += 1;
				
				arbre = creerNode(t[*i], arbre, Synt(t, tmp_var));
				
				break;
			}
			default: break;
		}
		(*i)++;
	}
	
	return arbre;
}
