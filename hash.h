#ifndef HEADER_HASH
#define HEADER_HASH

#include "astree.h"

#define SYMBOL_LIT_INT    1
#define SYMBOL_LIT_FLOAT  2
#define SYMBOL_LIT_TRUE   3
#define SYMBOL_LIT_FALSE  4
#define SYMBOL_LIT_CHAR   5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

#define DT_INT       100
#define DT_CHAR      101
#define DT_REAL      102
#define DT_BOOL      103
#define DT_UNDEFINED 104
#define DT_NOT_SET   105

#define NATURE_VETOR     110
#define NATURE_ESCALAR   112
#define NATURE_FUNCAO    113
#define NATURE_UNDEFINED 114

#define HASH_SIZE 997

//definições da tabela hash e assinaturas de funções sobre essa estrutura

typedef struct hash_node_struct{
	int type;
	char *text;
	int dataType;
	int nature;
	struct ASTREE *declaration;
	struct hash_node_struct *next;
} HASH_NODE;

HASH_NODE *Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

#endif
