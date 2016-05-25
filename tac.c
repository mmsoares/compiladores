#include "tac.h"
#include <stdio.h>
#include <stdlib.h>

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
	int i;

	TAC_NODE* code[MAX_SONS];

	for(i=0; i < MAX_SONS; i++) {
		code[i] = NULL;
	}

	if(syntaxtree == NULL) return NULL;

	for (i=0; i < MAX_SONS; i++) {
		code[i] = generateTacCode(syntaxtree->son[i]);
	}
		
	switch (syntaxtree->type) {
		 case AST_PROGRAMA:
		 	return code[0];
		 case AST_DECLARACOES:
		 	return joinTacs(code[0], code[1]);
		 case AST_VARIAVEL:
		 	return createTacNode(TAC_DECLARACAO_VARIAVEL, code[0]->result, code[2]->result, NULL);
		 case AST_VETOR_VAZIO:
		 case AST_VETOR:
			return createTacNode(TAC_DECLARACAO_VETOR, code[0]->result, code[2]->result, code[3]->result);
		 case AST_INI_VETOR:
		 	
		 case AST_LISTA_LITERAIS:
		 case AST_FUNCAO:
		 case AST_PARAMETRO:
		 case AST_LISTA_PARAMETRO:
		 case AST_COMANDOS:
		 	return NULL;
		 case AST_BLOCO:
		 case AST_LISTA_PARAM_CHAMADA:
		 case AST_ACESSO_VETOR:
		 case AST_CHAMADA_FUNCAO:
		 case AST_EXPRESSAO_PARENTESES:
		 case AST_OP_SOMA:
		 	return tac_createOperation(TAC_OP_SOMA, code[0], code[1]);
		 case AST_OP_SUB:
		 	return tac_createOperation(TAC_OP_SUB, code[0], code[1]);
		 case AST_OP_MUL:
			 return tac_createOperation(TAC_OP_MUL, code[0], code[1]);
		 case AST_OP_DIV:
		 	return tac_createOperation(TAC_OP_DIV, code[0], code[1]);
		 case AST_OP_MENOR:
		 	return tac_createOperation(TAC_OP_MENOR, code[0], code[1]);
		 case AST_OP_MAIOR:
		 	return tac_createOperation(TAC_OP_MAIOR, code[0], code[1]);
		 case AST_OP_LE:
		 	return tac_createOperation(TAC_OP_LE, code[0], code[1]);
		 case AST_OP_GE:
		 	return tac_createOperation(TAC_OP_GE, code[0], code[1]);
		 case AST_OP_EQ:
		 	return tac_createOperation(TAC_OP_EQ, code[0], code[1]);
		 case AST_OP_NE:
		 	return tac_createOperation(TAC_OP_NE, code[0], code[1]);
		 case AST_OP_AND:
		 	return tac_createOperation(TAC_OP_AND, code[0], code[1]);
		 case AST_OP_OR:
		 	return tac_createOperation(TAC_OP_OR, code[0], code[1]);
		 case AST_ATRIBUICAO:
		 case AST_ATRIBUICAO_VETOR:
		 case AST_IF:
		 case AST_IF_ELSE:
		 case AST_WHILE:
		 case AST_INPUT:
		 case AST_LISTA_VARIAVEIS:
		 case AST_OUTPUT:
		 case AST_LISTA_ELEM_EXP:
		 case AST_LISTA_ELEM_STRING:
		 case AST_RETURN:
		 case AST_KW_INT:
		 	return createTacNode(TAC_KW_INT, syntaxtree->symbol, NULL, NULL);
		 case AST_KW_BOOL:
		 	return createTacNode(TAC_KW_BOOL, syntaxtree->symbol, NULL, NULL);
		 case AST_KW_REAL:
		 	return createTacNode(TAC_KW_REAL, syntaxtree->symbol, NULL, NULL);
		 case AST_KW_CHAR:
		 	return createTacNode(TAC_KW_CHAR, syntaxtree->symbol, NULL, NULL);
		 case AST_LIT_INT:
		 	return createTacNode(TAC_SYMBOL, syntaxtree->symbol, NULL, NULL);
		 case AST_LIT_REAL:
		 	return createTacNode(TAC_SYMBOL, syntaxtree->symbol, NULL, NULL);
		 case AST_LIT_TRUE:
		 	return createTacNode(TAC_SYMBOL, syntaxtree->symbol, NULL, NULL);
		 case AST_LIT_FALSE:
		 	return createTacNode(TAC_SYMBOL, syntaxtree->symbol, NULL, NULL);
		 case AST_LIT_CHAR:
		 	return createTacNode(TAC_SYMBOL, syntaxtree->symbol, NULL, NULL);
		 case AST_LIT_STRING:
		 	return createTacNode(TAC_SYMBOL, syntaxtree->symbol, NULL, NULL);
		 case AST_IDENTIFIER:
		 case AST_COMANDO_VAZIO:
		 case AST_SYMBOL:
		 case AST_SYMBOL_VAR:
		 	return createTacNode(TAC_SYMBOL_VAR, syntaxtree->symbol, NULL, NULL);
		 case AST_SYMBOL_VET:
		 	return createTacNode(TAC_SYMBOL_VET, syntaxtree->symbol, NULL, NULL);
		 case AST_SYMBOL_FUN:
		 	break;
		 default:
		 	break;
	}
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
	HASH_NODE* tempNode = makeTemp();

	if (code0 != NULL) {
		if (code1 != NULL) {
			return joinTacs(joinTacs(code0, code1), createTacNode(type, tempNode, code0->result, code1->result));
		} else {
			return joinTacs(joinTacs(code0, code1), createTacNode(type, tempNode, code0->result, NULL));
		}
	} else {
		if (code1 != NULL) {
			return joinTacs(joinTacs(code0, code1), createTacNode(type, tempNode, NULL, code1->result));
		} else {
			return joinTacs(joinTacs(code0, code1), createTacNode(type, tempNode, NULL, NULL));
		}
	}
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
		case TAC_DECLARACAO_VARIAVEL: fprintf(stderr, "TAC_DECLARACAO_VARIAVEL "); break;
		case TAC_KW_INT: fprintf(stderr, "TAC_KW_INT "); break;
		default: fprintf(stderr, "UNKNOWN %d ", tac->type); break;
	}

	if(tac->result)    fprintf(stderr, "res=[%s] ", tac->result->text);
	if(tac->operator1) fprintf(stderr, "op1=[%s] ", tac->operator1->text);
	if(tac->operator2) fprintf(stderr, "op2=[%s] ", tac->operator2->text);
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