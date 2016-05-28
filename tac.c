#include "tac.h"
#include <string.h>
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
	for(aux = tac2; aux->previous != NULL; aux = aux->previous);
	aux->previous = tac1;
	return tac2;
}

TAC_NODE* createVectorRead(HASH_NODE* simbolo, TAC_NODE* indice) {
	HASH_NODE* temp = makeTemp();

	return joinTacs(indice, createTacNode(TAC_VECTOR_READ, temp, simbolo, indice->result));
}

TAC_NODE* createFunctionDeclaration(HASH_NODE* simbolo, TAC_NODE* listaParametros, TAC_NODE* listaComandos) {
	listaParametros = joinTacs(createTacNode(TAC_COMECO_FUNCAO, simbolo, NULL, NULL), listaParametros);
	listaComandos = joinTacs(listaParametros, listaComandos);
	return joinTacs(listaComandos, createTacNode(TAC_FINAL_FUNCAO, simbolo, NULL, NULL));
}

TAC_NODE* createFunctionCall(HASH_NODE* result, TAC_NODE* code) {
	TAC_NODE* aux;
	TAC_NODE* list;
	TAC_NODE* push;
	TAC_NODE* pop;

	for(aux=revertTac(code);aux;aux=aux->next) {
		pop = createTacNode(TAC_POP_PARAMETRO, aux->result, NULL, NULL);
		list = joinTacs(pop, list);
	}
	HASH_NODE* tempNode = makeTemp();
	list = joinTacs(createTacNode(TAC_FUNCTION_CALL, tempNode, result, NULL), list);

	for(aux=code; aux; aux=aux->previous) {
		push = createTacNode(TAC_PUSH_PARAMETRO, aux->result, NULL, NULL);
		list = joinTacs(push, list);
	}
	
	return list;
}

TAC_NODE* resultAtribuicao(TAC_NODE* code){
	TAC_NODE* popList = code;

	while(popList){
		if(popList->type != TAC_POP_PARAMETRO){
			break;
		}
		popList=popList->previous;
	}

	return popList;
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
			if(code[2]!=NULL) {
			 	return createTacNode(TAC_DECLARACAO_VARIAVEL, code[0]->result, code[2]->result, NULL);
			}
			else {
				return createTacNode(TAC_SYMBOL, code[0]->result, NULL, NULL);
			}
		 case AST_VETOR_VAZIO:
		 	return createTacNode(TAC_DECLARACAO_VETOR_VAZIO, code[0]->result, code[2]->result, NULL);
		 case AST_VETOR:
		 	return joinTacs(createTacNode(TAC_DECLARACAO_VETOR, code[0]->result, code[2]->result, NULL), initializeVector(revertTac(code[3]),code[0]->result,0));
		 case AST_INI_VETOR:
		 	return joinTacs(code[0], code[1]);
		 case AST_LISTA_LITERAIS:
		 	return joinTacs(code[0], code[1]);
		 case AST_FUNCAO:
		 	return createFunctionDeclaration(code[0]->result, code[2], code[3]);
		 case AST_PARAMETRO:
		 	return createTacNode(TAC_PARAMETRO, code[0]->result, code[1]->result, NULL);
		 case AST_LISTA_PARAMETRO:
		 	return joinTacs(code[0], code[1]);
		 case AST_COMANDOS:
		 	return joinTacs(code[0], code[1]);
		 case AST_BLOCO:
		 	return code[0];
		 case AST_LISTA_PARAM_CHAMADA:
			return joinTacs(code[0], code[1]);
		 case AST_ACESSO_VETOR:
		 	return createVectorRead(code[0]->result, code[1]);
		 case AST_CHAMADA_FUNCAO:
			return createFunctionCall(code[0]->result, code[1]);
		 case AST_EXPRESSAO_PARENTESES:
		 	return code[0];
		 case AST_OP_SOMA:
		 	return createTacOperation(TAC_OP_SOMA, code[0], code[1]);
		 case AST_OP_SUB:
		 	return createTacOperation(TAC_OP_SUB, code[0], code[1]);
		 case AST_OP_MUL:
			 return createTacOperation(TAC_OP_MUL, code[0], code[1]);
		 case AST_OP_DIV:
		 	return createTacOperation(TAC_OP_DIV, code[0], code[1]);
		 case AST_OP_MENOR:
		 	return createTacOperation(TAC_OP_MENOR, code[0], code[1]);
		 case AST_OP_MAIOR:
		 	return createTacOperation(TAC_OP_MAIOR, code[0], code[1]);
		 case AST_OP_LE:
		 	return createTacOperation(TAC_OP_LE, code[0], code[1]);
		 case AST_OP_GE:
		 	return createTacOperation(TAC_OP_GE, code[0], code[1]);
		 case AST_OP_EQ:
		 	return createTacOperation(TAC_OP_EQ, code[0], code[1]);
		 case AST_OP_NE:
		 	return createTacOperation(TAC_OP_NE, code[0], code[1]);
		 case AST_OP_AND:
		 	return createTacOperation(TAC_OP_AND, code[0], code[1]);
		 case AST_OP_OR:
		 	return createTacOperation(TAC_OP_OR, code[0], code[1]);
		 case AST_ATRIBUICAO:
		 	return joinTacs(code[1], createTacNode(TAC_ATRIBUICAO, code[0]->result, resultAtribuicao(code[1])->result, NULL));
		 case AST_ATRIBUICAO_VETOR:
		 	return createAssignVector(code[0]->result, resultAtribuicao(code[1]), resultAtribuicao(code[2]));
		 case AST_IF:
		 case AST_IF_ELSE:
		 case AST_WHILE:
		 case AST_INPUT:
		 case AST_LISTA_VARIAVEIS:
		 case AST_OUTPUT:
		 case AST_LISTA_ELEM_EXP:
		 case AST_LISTA_ELEM_STRING:
		 case AST_RETURN:
			return joinTacs(code[0], createTacNode(TAC_RETURN, code[0]->result, NULL, NULL));
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
		 case AST_COMANDO_VAZIO:
		 	return NULL;
		 case AST_SYMBOL_VAR:
			/*fprintf(stderr, "Entrando no ast_symbol_var, astree node=");
			printNode(syntaxtree,0);
			fprintf(stderr, "  hash node=");
			HASH_NODE* node = syntaxtree->symbol;
			printf("Table[%d] = type: %d, value: %s, dataType: %d, nature: %d\n",i,node->type, node->text, node->dataType, node->nature);
*/
		 	return createTacNode(TAC_SYMBOL_VAR, syntaxtree->symbol, NULL, NULL);
	//		fprintf(stderr, "Saindo do ast_symbol_var\n");
		 case AST_SYMBOL_VET:
		 	return createTacNode(TAC_SYMBOL_VET, syntaxtree->symbol, NULL, NULL);
		 case AST_SYMBOL_FUN:
		 	return createTacNode(TAC_SYMBOL_FUN, syntaxtree->symbol, NULL, NULL);
		 default:
		 	break;
	}
}

TAC_NODE* initializeVector(TAC_NODE* initializeList, HASH_NODE* vector, int i){

	if(initializeList == NULL){
		return initializeList;
	}else{
		char str[25];	
		sprintf(str,"%d", i);
		HASH_NODE* index = hashInsert(str, SYMBOL_LIT_INT);
		return joinTacs(createTacNode(TAC_VECTOR_ASSIGN, vector, index, initializeList->result), initializeVector(initializeList->next, vector, ++i));
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

TAC_NODE* createTacOperation(int type, TAC_NODE* code0, TAC_NODE* code1) {
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

TAC_NODE* createAssignVector(HASH_NODE* simbolo, TAC_NODE* indice, TAC_NODE* valor) {
	if (indice != NULL) {
		if (valor != NULL) {
			return joinTacs(joinTacs(indice, valor), createTacNode(TAC_VECTOR_ASSIGN, simbolo, indice->result, valor->result));
		} else {
			return joinTacs(joinTacs(indice, valor), createTacNode(TAC_VECTOR_ASSIGN, simbolo, indice->result, NULL));
		}
	} else {
		if (valor != NULL) {
			return joinTacs(joinTacs(indice, valor), createTacNode(TAC_VECTOR_ASSIGN, simbolo, NULL, valor->result));
		} else {
			return joinTacs(joinTacs(indice, valor), createTacNode(TAC_VECTOR_ASSIGN, simbolo, NULL, NULL));
		}
	}
}


TAC_NODE* tac_createOutput(TAC_NODE* expression, TAC_NODE* next) {

}

void printTacNode(TAC_NODE* tac) {
	if(tac == NULL || tac->type == TAC_SYMBOL) return;

	switch(tac->type) {
		//case TAC_SYMBOL:  fprintf(stderr, "TAC_SYMBOL "); break;
		case TAC_DECLARACAO_VARIAVEL: fprintf(stderr, "TAC_DECLARACAO_VARIAVEL "); break;
		case TAC_DECLARACAO_VETOR: fprintf(stderr, "TAC_DECLARACAO_VETOR "); break;
		case TAC_DECLARACAO_VETOR_VAZIO: fprintf(stderr, "TAC_DECLARACAO_VETOR_VAZIO "); break;
		case TAC_COMECO_FUNCAO: fprintf(stderr, "TAC_COMECO_FUNCAO "); break;
		case TAC_PARAMETRO: fprintf(stderr, "TAC_PARAMETRO "); break;
		case TAC_FINAL_FUNCAO: fprintf(stderr, "TAC_FINAL_FUNCAO "); break;
		case TAC_ATRIBUICAO: fprintf(stderr, "TAC_ATRIBUICAO "); break;
		case TAC_VECTOR_ASSIGN: fprintf(stderr, "TAC_VECTOR_ASSIGN "); break;
		case TAC_VECTOR_READ: fprintf(stderr, "TAC_VECTOR_READ "); break;
		case TAC_OP_SOMA: fprintf(stderr, "TAC_OP_SOMA "); break;
		case TAC_OP_SUB: fprintf(stderr, "TAC_OP_SUB "); break;
		case TAC_OP_MUL: fprintf(stderr, "TAC_OP_MUL "); break;
		case TAC_OP_DIV: fprintf(stderr, "TAC_OP_DIV "); break;
		case TAC_OP_MENOR: fprintf(stderr, "TAC_OP_MENOR "); break;
		case TAC_OP_MAIOR: fprintf(stderr, "TAC_OP_MAIOR "); break;
		case TAC_OP_LE: fprintf(stderr, "TAC_OP_LE "); break;
		case TAC_OP_GE: fprintf(stderr, "TAC_OP_GE "); break;
		case TAC_OP_EQ: fprintf(stderr, "TAC_OP_EQ "); break;
		case TAC_OP_NE: fprintf(stderr, "TAC_OP_NE "); break;
		case TAC_OP_AND: fprintf(stderr, "TAC_OP_AND "); break;
		case TAC_OP_OR: fprintf(stderr, "TAC_OP_OR "); break;
		case TAC_KW_INT: fprintf(stderr, "TAC_KW_INT "); break;
		case TAC_KW_BOOL: fprintf(stderr, "TAC_KW_BOOL "); break;
		case TAC_KW_CHAR: fprintf(stderr, "TAC_KW_CHAR "); break;
		case TAC_KW_REAL: fprintf(stderr, "TAC_KW_REAL "); break;
		case TAC_SYMBOL_VAR: fprintf(stderr, "TAC_SYMBOL_VAR "); break;
		case TAC_SYMBOL_VET: fprintf(stderr, "TAC_SYMBOL_VET "); break;
		case TAC_SYMBOL_FUN: fprintf(stderr, "TAC_SYMBOL_FUN "); break;
		case TAC_RETURN: fprintf(stderr, "TAC_RETURN "); break;
		case TAC_PUSH_PARAMETRO: fprintf(stderr, "TAC_PUSH_PARAMETRO "); break;
		case TAC_POP_PARAMETRO: fprintf(stderr, "TAC_POP_PARAMETRO "); break;
		case TAC_FUNCTION_CALL: fprintf(stderr, "TAC_FUNCTION_CALL "); break;
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
