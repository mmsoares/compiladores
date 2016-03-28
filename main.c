#include <stdio.h>
#include "hash.h"
#include "y.tab.h"

extern int isRunning(void);

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
