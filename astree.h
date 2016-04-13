#include    "hash.h"

#ifndef     ASTREE_HEADER
#define     ASTREE_HEADER

#define MAX_SONS 4

typedef struct astree_node {
    int type;
    hash_t* symbol;
    struct ast_node *son[MAX_SONS];
} ASTREE;

FILE    *input;
FILE    *outputFile;

ASTREE* astreeCreate(int type, hash_t *symbol, ASTREE *s0,ASTREE *s1, ASTREE *s2, ASTREE *s3);
void    astreePrint(ASTREE* node, int level);
void    decompile(ASTREE *root);

#endif