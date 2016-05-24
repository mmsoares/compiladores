#include "tac.h"
#include <stdio.h>
#include <stdlib.h>

int labelCounter = 0;
int tempCounter = 0;

TAC_NODE* createTacNode(int type, HASH_NODE* result, HASH_NODE* operation1, HASH_NODE* operation2) {
	TAC_NODE* node = 0;
	node = (TAC_NODE*) calloc(1, sizeof(TAC_NODE));
	node->type = type;
	node->result = result;
	node->operator1 = operation1;
	node->operator2 = operation2;
	node->previous = NULL;
	node->next = NULL;
	return node;
}

TAC_NODE* joinTacs(TAC_NODE* tac1, TAC_NODE* tac2) {
	if(tac1==NULL) return tac2;
	if(tac2==NULL) return tac1;

	TAC_NODE* aux;
	for(aux = tac2; aux->previous != NULL; aux = aux->previous);   //move o iterador auxiliar até o primeiro elemento do tac
	aux->previous = tac1;
	return tac2;
}

TAC_NODE* generateTacCode(ASTREE* syntaxtree) {

}

TAC_NODE* revertTac(TAC_NODE* tac) {
	TAC_NODE* aux;

	if(tac==NULL) return tac;

	for (aux = tac; aux->previous != NULL; aux = aux->previous) {
		aux->previous->next = aux;
	}
	return aux;
}

TAC_NODE* tac_createOperation(int type, TAC_NODE* code0, TAC_NODE* code1) {

}

TAC_NODE* tac_createIfThen(TAC_NODE* code0, TAC_NODE* code1) {

}

TAC_NODE* tac_createIfElse(TAC_NODE* code0, TAC_NODE* code1) {

}

TAC_NODE* tac_createIfLoop(TAC_NODE* code0, TAC_NODE* code1) {

}

TAC_NODE* tac_createVectorInitialization(TAC_NODE* literal, TAC_NODE* next) {

}

TAC_NODE* tac_createAssignVector(HASH_NODE* symbol, TAC_NODE* index, TAC_NODE* attribute) {

}

TAC_NODE* tac_createVectorRead(HASH_NODE* symbol, TAC_NODE* index) {

}

TAC_NODE* tac_createFunctionDeclaration(HASH_NODE* symbol, TAC_NODE* parameter_list, TAC_NODE* statement_list) {

}

TAC_NODE* tac_createFunctionParameters(HASH_NODE* symbol, TAC_NODE* next) {

}

TAC_NODE* tac_createFunctionCall(HASH_NODE* symbol, TAC_NODE* params) {

}

TAC_NODE* tac_createFunctionArguments(HASH_NODE* symbol, TAC_NODE* expression, TAC_NODE* next) {

}

TAC_NODE* tac_createOutput(TAC_NODE* expression, TAC_NODE* next) {

}

void printTacNode(TAC_NODE* tac) {
	if(tac == NULL) return;

	switch(tac->type) {
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL "); break;
		default: fprintf(stderr, "UNKNOWN %d", tac->type); break;
	}

	if(tac->result)    fprintf(stderr, "res=[%s] ", tac->result->key)
	if(tac->operator1) fprintf(stderr, "op1=[%s] ", tac->operator1->key);
	if(tac->operator2) fprintf(stderr, "op2=[%s] ", tac->operator2->key);
	fprintf(stderr, "\n");
}

void printTacList(TAC_NODE* tac) {
	if(tac != NULL) {
		printTacNode(tac);
		printTacList(tac->next);
	}
}

void printTacListReverse(TAC_NODE* tac) {
	if(tac != NULL) {
		printTacListReverse(tac->previous);
		printTacNode(tac);
	}
}