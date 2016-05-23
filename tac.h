#ifndef     TAC_HEADER
#define     TAC_HEADER

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL			01
#define TAC_VECTOR			02
#define TAC_LITERAL			03
#define TAC_LABEL			04
#define TAC_TEMP			05
#define TAC_POINTER			06
#define TAC_ADDRESS			07

#define TAC_OP_PLUS			11
#define TAC_OP_MINUS		12
#define TAC_OP_TIMES		13
#define TAC_OP_DIVIDE		14
#define TAC_OP_MODULE		15

#define TAC_OP_EQUAL		21
#define TAC_OP_NOTEQUAL		22
#define TAC_OP_LESSER		23
#define TAC_OP_GREATER		24
#define TAC_OP_LESSEREQUAL	25
#define TAC_OP_GREATEREQUAL	26
#define TAC_OP_AND			27
#define TAC_OP_OR			28
#define TAC_OP_NOT			29

#define TAC_ASSIGN_VAR		31
#define TAC_JUMP			32
#define TAC_IF_THEN			33
#define TAC_IF_ELSE			34
#define TAC_OUTPUT			35
#define TAC_INPUT			36
#define TAC_RETURN			37

#define TAC_WORD			41
#define TAC_BOOL			42
#define TAC_BYTE			43

#define TAC_VARIABLE_DECLARATION	51

#define TAC_FUNCTION_DECLARATION	61 
#define TAC_FUNCTION_PARAMS			62
#define TAC_FUNCTION_BEGIN			63
#define TAC_FUNCTION_END			64
#define TAC_FUNCTION_CALL			65
#define TAC_FUNCTION_ARGUMENTS		66

#define TAC_VECTOR_DECLARATION		71
#define TAC_VECTOR_INIT				72
#define TAC_VECTOR_READ				73
#define TAC_VECTOR_WRITE			74

#define TAC_POINTER_DECLARATION		82


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

char* makeLabel();
char* makeTemp();

#endif
