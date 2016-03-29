#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
 
extern int isRunning();
extern int getLineNumber();
extern void initMe();

int main()
{	
	initMe();

	while (isRunning())
	{
		yyparse();
	}

   	hashPrint();

	return 0;
}
