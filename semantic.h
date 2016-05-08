#ifndef HEADER_SEMANTIC
#define HEADER_SEMANTIC

#include "astree.h"
#include "hash.h"

void performSemanticValidations(HASH_NODE* hashmap, ASTREE* syntaxtree);
int  getSymbolDeclarations(HASH_NODE *node, ASTREE *root);
void checkDeclaration(ASTREE* syntaxtree);
void checkTypes(ASTREE* syntaxtree);
void checkCodeType(ASTREE* functionType, ASTREE* functionName, ASTREE* node);

#endif
