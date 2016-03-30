#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"
#include "lex.yy.h"
 
extern int isRunning();
extern int getLineNumber();
extern void initMe();

int main(int argc, char **argv)
{	
	initMe();

	if (argc<2)
	{
		fprintf(stderr, "ERRO! Para rodar, passe o nome de um arquivo junto.\n");
		exit (1);
	}
	if ((yyin = fopen(argv[1], "r"))==0)
	{
		fprintf(stderr, "ERRO! Nao foi possivel abrir este arquivo.\n");
		exit (1);
	}

	yyparse();
   	hashPrint();

	return 0;
}
