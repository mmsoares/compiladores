#ifndef HEADER_HASH
#define HEADER_HASH

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLOAT 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7


#define HASH_SIZE 997

//definições da tabela hash e assinaturas de funções sobre essa estrutura

typedef struct hash_node_struct{
	int type;
	char *text;
	struct hash_node_struct *next;
} HASH_NODE;

HASH_NODE *Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

#endif
