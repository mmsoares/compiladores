#ifndef     TAC_HEADER
#define     TAC_HEADER

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL 1
#define TAC_MOVE   2
#define TAC_ADD    3
#define TAC_SUB    4
#define TAC_MUL	   5
#define TAC_DIV    6

#define TAC_LABEL  20

#define TAC_BEGINFUN 21
#define TAC_ENDFUN   22
#define TAC_IFZ      23
#define TAC_JUMP     24
#define TAC_CALL     25
#define TAC_ARG      26
#define TAC_RET      27
#define TAC_PRINT    28
#define TAC_READ     29


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
TAC_NODE* revertTac(TAC_NODE* tac);
TAC_NODE* tac_createOperation(int type, TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createIfThen(TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createIfElse(TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createIfLoop(TAC_NODE* code0, TAC_NODE* code1);
TAC_NODE* tac_createVectorInitialization(TAC_NODE* literal, TAC_NODE* next);
TAC_NODE* tac_createAssignVector(HASH_NODE* symbol, TAC_NODE* index, TAC_NODE* attribute);
TAC_NODE* tac_createVectorRead(HASH_NODE* symbol, TAC_NODE* index);
TAC_NODE* tac_createFunctionDeclaration(HASH_NODE* symbol, TAC_NODE* parameter_list, TAC_NODE* statement_list);
TAC_NODE* tac_createFunctionParameters(HASH_NODE* symbol, TAC_NODE* next);
TAC_NODE* tac_createFunctionCall(HASH_NODE* symbol, TAC_NODE* params);
TAC_NODE* tac_createFunctionArguments(HASH_NODE* symbol, TAC_NODE* expression, TAC_NODE* next);
TAC_NODE* tac_createOutput(TAC_NODE* expression, TAC_NODE* next);

void printTacNode(TAC_NODE* tac);
void printTacList(TAC_NODE* tac);
void printTacListReverse(TAC_NODE* tac);

#endif
