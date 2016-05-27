#ifndef     TAC_HEADER
#define     TAC_HEADER

#include "hash.h"
#include "astree.h"

#define TAC_DECLARACAO_VARIAVEL 1
#define TAC_DECLARACAO_VETOR 2
#define TAC_DECLARACAO_VETOR_VAZIO 3
#define TAC_ATRIBUICAO 4
#define TAC_VECTOR_ASSIGN 5
#define TAC_COMECO_FUNCAO 6
#define TAC_FINAL_FUNCAO  7
#define TAC_PARAMETRO 8

#define TAC_KW_INT 20
#define TAC_KW_BOOL 21
#define TAC_KW_CHAR 22
#define TAC_KW_REAL 23

#define TAC_SYMBOL 30
#define TAC_OP_SOMA 31
#define TAC_OP_SUB 32
#define TAC_OP_MUL 33
#define TAC_OP_DIV 34
#define TAC_OP_MENOR 35
#define TAC_OP_MAIOR 36
#define TAC_OP_LE 37
#define TAC_OP_GE 38
#define TAC_OP_EQ 39
#define TAC_OP_NE 40
#define TAC_OP_AND 41
#define TAC_OP_OR 42

#define TAC_SYMBOL_VAR 50
#define TAC_SYMBOL_VET 51
#define TAC_SYMBOL_FUN 52


typedef struct tac_node {
	int type;
	HASH_NODE* result;
	HASH_NODE* operator1;
	HASH_NODE* operator2;
	struct tac_node* previous;
	struct tac_node* next;
} TAC_NODE;

TAC_NODE* createTacNode(int type, HASH_NODE* result, HASH_NODE* operation1, HASH_NODE* operation2);
TAC_NODE* joinTacs(TAC_NODE* tac1, TAC_NODE* tac2);
TAC_NODE* generateTacCode(ASTREE* syntaxtree);
TAC_NODE* initializeVector(TAC_NODE* initializeList, HASH_NODE* vector, int i);
TAC_NODE* revertTac(TAC_NODE* tac);
TAC_NODE* createTacOperation(int type, TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* createFunctionDeclaration(HASH_NODE* simbolo, TAC_NODE* listaParametros, TAC_NODE* listaComandos);

TAC_NODE* tac_createIfThen(TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createIfElse(TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createIfLoop(TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createVectorInitialization(TAC_NODE* literal, TAC_NODE* next);
TAC_NODE* tac_createAssignVector(HASH_NODE* symbol, TAC_NODE* index, TAC_NODE* attribute);
TAC_NODE* tac_createVectorRead(HASH_NODE* symbol, TAC_NODE* index);
TAC_NODE* tac_createFunctionParameters(HASH_NODE* symbol, TAC_NODE* next);
TAC_NODE* tac_createFunctionCall(HASH_NODE* symbol, TAC_NODE* params);
TAC_NODE* tac_createFunctionArguments(HASH_NODE* symbol, TAC_NODE* expression, TAC_NODE* next);
TAC_NODE* tac_createOutput(TAC_NODE* expression, TAC_NODE* next);

void printTacNode(TAC_NODE* tac);
void printTacList(TAC_NODE* tac);
void printTacListReverse(TAC_NODE* tac);

#endif
