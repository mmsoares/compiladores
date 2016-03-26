#define HASH_SIZE 997

//definições da tabela hash e assinaturas de funções sobre essa estrutura

typedef struct hash_node_struct{
	int type;
	char *text;
	struct hash_node_struct *next;
} HASH_NODE;


void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
