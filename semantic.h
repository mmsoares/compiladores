#ifndef HEADER_SEMANTIC
#define HEADER_SEMANTIC

#include "astree.h"

void performSemanticValidations(struct hash_node_struct* hashmap, struct astree_struct* syntaxtree);
void checkDeclaration(struct astree_struct* syntaxtree);
void checkParameterDeclaration(struct astree_struct* parameterList);
void checkUndeclaredVariables(struct hash_node_struct* hashmap);
void checkTypes(struct astree_struct* syntaxtree);
void checkCodeType(struct astree_struct* functionType, struct astree_struct* functionName, struct astree_struct* node);

#endif
