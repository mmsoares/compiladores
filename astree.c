#include "astree.h"
#include "hash.h"

ASTREE* astreeCreate(int type, HASH_NODE *symbol, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3) {
	ASTREE *newnode = 0;
	newnode = (ASTREE*) calloc(1,sizeof(ASTREE));
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;

	return newnode;
}

void astreePrint(ASTREE* node, int level) {

}

void decompile(ASTREE *root) {

}
