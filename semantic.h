#ifndef HEADER_SEMANTIC
#define HEADER_SEMANTIC

#include "astree.h"
#include "hash.h"

void performSemanticValidations(HASH_NODE* hashmap, ASTREE* syntaxtree);
void setNature(ASTREE *root);
int  getSymbolDeclarations(HASH_NODE *node, ASTREE *root);
void checkDeclaration(ASTREE* syntaxtree);
void checkUsage(ASTREE* node);
void checkParameters(ASTREE* node);
void setDataTypeToVarKwAndLit(ASTREE *node);
void setDataTypeToVarUsage(ASTREE* node);
//int checkType(ASTREE* node);

#endif
