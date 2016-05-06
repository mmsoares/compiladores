#ifndef HEADER_SEMANTIC
#define HEADER_SEMANTIC

#include "astree.h"

void semantic_check(struct hash_node_struct* hashmap, struct astree_struct* syntaxtree);
void semantic_declaration(struct astree_struct* syntaxtree);
void semantic_parameterDeclaration(struct astree_struct* parameterList);
void semantic_undeclared(struct hash_node_struct* hashmap);
void semantic_types(struct astree_struct* syntaxtree);
void semantic_codeType(struct astree_struct* functionType, struct astree_struct* functionName, struct astree_struct* node);

#endif
