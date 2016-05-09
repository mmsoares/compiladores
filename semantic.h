#ifndef HEADER_SEMANTIC
#define HEADER_SEMANTIC

#include "astree.h"
#include "hash.h"

void performSemanticValidations(HASH_NODE* hashmap, ASTREE* syntaxtree);
void setNature(ASTREE *root);
int  getSymbolDeclarations(HASH_NODE *node, ASTREE *root);
void checkDeclaration(ASTREE* syntaxtree);
void checkUsage(ASTREE* node);
void setDataTypeToVarKwAndLit(ASTREE *node);
void setDataTypeToVarUsage(ASTREE* node);
void setDataTypeToVar(ASTREE *node);
void setUndefinedDataTypes(ASTREE *node);
void setDataTypeToVarFather(ASTREE *node);
int  getDominantType(int type1, int type2, int isDiv);
void checkParameterCompatibility(int type1, int type2);
void checkFunctionParameters(ASTREE *node);
void checkBiggerParameterLists(ASTREE* declaration, ASTREE* call);
void checkTypesForVectorInitializations(ASTREE* node);
void checkTypesForVector(ASTREE* node, int vectorType);
int  setTypesToAttrAndOperations(ASTREE* node);
void searchFunctions(ASTREE *node);
void checkReturns(ASTREE *node, int functionType);

#endif
