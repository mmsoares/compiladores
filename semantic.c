#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"
#include "semantic.h"

void performSemanticValidations(HASH_NODE* hashmap, ASTREE* syntaxtree) {
	setNature(syntaxtree);
	checkDeclaration(syntaxtree);
	checkUsage(syntaxtree);	
	setDataTypeToVarKwAndLit(syntaxtree);
	setDataTypeToVarUsage(syntaxtree);
	setUndefinedDataTypes(syntaxtree);
	setDataTypeToVarFather(syntaxtree);
	checkFunctionParameters(syntaxtree);
	setTypesToAttrAndOperations(syntaxtree);
	astreePrint(syntaxtree, 0);
}

void setNature(ASTREE *root) {
	ASTREE *declarations;

	for(declarations = root->son[0];declarations!=NULL;declarations=declarations->son[1]) {	
		switch(declarations->son[0]->type){
			case AST_VARIAVEL:
				declarations->son[0]->son[0]->symbol->nature = NATURE_ESCALAR;
				break;
			case AST_VETOR:
			case AST_VETOR_VAZIO:
				declarations->son[0]->son[0]->symbol->nature = NATURE_VETOR;
				break;
			case AST_FUNCAO:
				declarations->son[0]->son[0]->symbol->nature = NATURE_FUNCAO;
				break;
			default:
				break;
		}
	}

	HASH_NODE *node = 0;
	int i;

	for(i=0;i<HASH_SIZE;i++){
		for(node = Table[i];node;node = node->next){
			if(node->type == SYMBOL_IDENTIFIER && node->nature == NATURE_UNDEFINED) {
				node->nature = NATURE_ESCALAR;
			}
		}
	}
}

int getSymbolDeclarations(HASH_NODE *node, ASTREE *root) {
	int numOfDeclarations = 0;
	ASTREE *declarations;

	for(declarations = root->son[0];declarations!=NULL;declarations=declarations->son[1]) {
		if(strcmp(declarations->son[0]->son[0]->symbol->text, node->text)==0){
			numOfDeclarations++;
		}

		if(declarations->son[0]->type == AST_FUNCAO) {
			if(declarations->son[0]->son[2]){
				if(declarations->son[0]->son[2]->type == AST_PARAMETRO){
					if(strcmp(declarations->son[0]->son[2]->son[0]->symbol->text, node->text)==0){
						numOfDeclarations++;
					}
				}
				if(declarations->son[0]->son[2]->type == AST_LISTA_PARAMETRO){
					ASTREE *aux;
					for(aux=declarations->son[0]->son[2];aux;aux=aux->son[1]){
						if(strcmp(aux->son[0]->son[0]->symbol->text, node->text)==0){
							numOfDeclarations++;
						}
						if(aux->son[1]->type == AST_PARAMETRO){
							if(strcmp(aux->son[1]->son[0]->symbol->text, node->text)==0){
								numOfDeclarations++;
							}
							break;
						}
					}
				}
			}
		}
	}

	return numOfDeclarations;
}

void checkDeclaration(ASTREE* root) {
	int i;
	HASH_NODE *hashNode = 0;
	for(i=0;i<HASH_SIZE;i++) {
		for(hashNode=Table[i];hashNode;hashNode=hashNode->next) {
			if(hashNode->type == SYMBOL_IDENTIFIER) {
				int declarations = getSymbolDeclarations(hashNode, root);

				if(declarations == 0) {
					fprintf(stderr, "Erro: simbolo %s nao foi declarado!\n", hashNode->text);
					exit(4);
				}
				if(declarations > 1) {
					fprintf(stderr, "Erro: simbolo %s foi declarado mais de uma vez!\n", hashNode->text);
					exit(4);
				}
			}
		}
	}
}

void checkUsage(ASTREE* node) {
	int i;
	
	if(node==0) return;

	switch(node->type) {
		case AST_SYMBOL_FUN:
			if(node->symbol->nature != NATURE_FUNCAO) {
				fprintf(stderr, "Uso incorreto do identificador %s como funcao\n", node->symbol->text);
				exit(4);
			}		
			break;
		case AST_SYMBOL_VAR:
			if(node->symbol->nature != NATURE_ESCALAR) {
				fprintf(stderr, "Uso incorreto do identificador %s como escalar\n", node->symbol->text);
				exit(4);
			}
			break;
		case AST_SYMBOL_VET:
			if(node->symbol->nature != NATURE_VETOR) {
				fprintf(stderr, "Uso incorreto do identificador %s como vetor\n", node->symbol->text);
				exit(4);
			}		
			break;
		default:
			break;
	}

	for(i=0;i<MAX_SONS;i++) {
		checkUsage(node->son[i]);
	}	
}

void checkParameters(ASTREE* node) {
	/*
	  procurar todas as chamadas de funcao e pra cada uma pegar quantos	
	  e de que tipo são os parametros
	  depois, procurar na definição da função pra ver se tem o número certo de 
	  parâmetros e se eles são compatíveis
	*/
 	int i;
	
	if(node==0) return;

	switch(node->type) {

	}
}

void setDataTypeToVarKwAndLit(ASTREE *node) {
	if(node==0) return;
	int i;

	switch(node->type) {
		case AST_KW_INT:
		case AST_LIT_INT:
			node->dataType = DT_INT;
			break;
		case AST_KW_REAL:
			node->dataType = DT_REAL;
			break;
		case AST_KW_CHAR:
		case AST_LIT_CHAR:
			node->dataType = DT_CHAR;
			break;
		case AST_KW_BOOL:
		case AST_LIT_TRUE:
		case AST_LIT_FALSE:
			node->dataType = DT_BOOL;
			break;
		default:
			break;
	}

	for(i=0;i<MAX_SONS;i++) {
		setDataTypeToVarKwAndLit(node->son[i]);
	}	
}

void setDataTypeToVarUsage(ASTREE* node) {
	if(node==0) return;
	int i;

	if(!node->dataType || node->dataType == DT_NOT_SET){
		switch(node->type) {
			case AST_SYMBOL_VAR:
			case AST_SYMBOL_VET:
			case AST_SYMBOL_FUN:
				node->dataType = node->symbol->dataType;		
				break;		
			default:
				break;
		}
	}
	
	for(i=0;i<MAX_SONS;i++) {
		setDataTypeToVarUsage(node->son[i]);
	}		
}

void setDataTypeToVar(ASTREE *node) {
	if(node==0) return;
	int i;

	if(!node->dataType || node->dataType == DT_NOT_SET){
		switch(node->type) {
			case AST_SYMBOL_VAR:
			case AST_SYMBOL_VET:
			case AST_SYMBOL_FUN:
				node->dataType = node->symbol->dataType;		
				break;		
			default:
				break;
		}
	}
	
	for(i=0;i<MAX_SONS;i++) {
		setDataTypeToVar(node->son[i]);
	}		
}

void setUndefinedDataTypes(ASTREE *node) {
	if(node==0) return;
	int i;

	switch(node->type) {
		case AST_BLOCO:
		case AST_PROGRAMA:
		case AST_LISTA_PARAMETRO:
		case AST_DECLARACOES:
		case AST_LISTA_LITERAIS:
		case AST_LISTA_ELEM_STRING:
		case AST_COMANDOS:
		case AST_COMANDO_VAZIO:
		case AST_OUTPUT:
		case AST_LISTA_VARIAVEIS:
		case AST_WHILE:
		case AST_IF:
		case AST_IF_ELSE:
		case AST_INPUT:
			node->dataType = DT_UNDEFINED;
			break;		
		default:
			break;
	}
	
	for(i=0;i<MAX_SONS;i++) {
		setUndefinedDataTypes(node->son[i]);
	}		
}

void setDataTypeToVarFather(ASTREE *node) {
	if(node==0) return;
	int i;

	switch(node->type) {
		case AST_CHAMADA_FUNCAO:
		case AST_VARIAVEL:
		case AST_ACESSO_VETOR:
		case AST_ATRIBUICAO_VETOR:
			node->dataType = node->son[0]->dataType;
			break;		
		default:
			break;
	}
	
	for(i=0;i<MAX_SONS;i++) {
		setDataTypeToVarFather(node->son[i]);
	}	
}

int getDominantType(int type1, int type2, int isDiv) {
	if(type1 == DT_INT && type2 == DT_INT) {
		if(isDiv==1) return DT_REAL;
		else return DT_INT;
	}
	if(type1 == DT_INT && type2 == DT_REAL) {
		return DT_REAL;
	}
	if(type1 == DT_INT && type2 == DT_CHAR) {
		if(isDiv==1) return DT_REAL;
		else return DT_INT;
	}
	if(type1 == DT_INT && type2 == DT_BOOL) {
		fprintf(stderr, "Error: erro de tipo entre %d e %d\n", type1, type2);
		exit(4);
	}	
	//
	if(type1 == DT_REAL && type2 == DT_INT) {
		return DT_REAL;
	}
	if(type1 == DT_REAL && type2 == DT_REAL) {
		return DT_REAL;
	}
	if(type1 == DT_REAL && type2 == DT_CHAR) {
		return DT_REAL;
	}
	if(type1 == DT_REAL && type2 == DT_BOOL) {
		fprintf(stderr, "Error: erro de tipo entre %d e %d\n", type1, type2);
		exit(4);
	}
	//
	if(type1 == DT_CHAR && type2 == DT_INT) {
		if(isDiv==1) return DT_REAL;
		else return DT_INT;
	}
	if(type1 == DT_CHAR && type2 == DT_REAL) {
		return DT_REAL;
	}
	if(type1 == DT_CHAR && type2 == DT_CHAR) {
		if(isDiv==1) return DT_REAL;
		else return DT_CHAR;
	}
	if(type1 == DT_CHAR && type2 == DT_BOOL) {
		fprintf(stderr, "Error: erro de tipo entre %d e %d\n", type1, type2);
		exit(4);
	}
	//
	if(type1 == DT_BOOL && type2 == DT_INT) {
		fprintf(stderr, "Error: erro de tipo entre %d e %d\n", type1, type2);
		exit(4);
	}
	if(type1 == DT_BOOL && type2 == DT_REAL) {
		fprintf(stderr, "Error: erro de tipo entre %d e %d\n", type1, type2);
		exit(4);
	}
	if(type1 == DT_BOOL && type2 == DT_CHAR) {
		fprintf(stderr, "Error: erro de tipo entre %d e %d\n", type1, type2);
		exit(4);
	}
	if(type1 == DT_BOOL && type2 == DT_BOOL) {
		return DT_BOOL;
	}

	return DT_UNDEFINED;
}

void checkParameterCompatibility(int type1, int type2){
	fprintf(stderr, "Checking compatibility between %d and %d\n", type1, type2);
	if(type1 == DT_BOOL) {
		if(type2 != DT_BOOL) {
			fprintf(stderr, "Erro: tipos nao compativeis na chamada de funcao\n");
			exit(4);
		}
	}
	else {
		if(type2 == DT_BOOL) {
			fprintf(stderr, "Erro: tipos nao compativeis na chamada de funcao\n");
			exit(4);
		}
	}
}

void checkFunctionParameters(ASTREE *node) {
	if(node==0) return;
	int i;

	if(node->type == AST_CHAMADA_FUNCAO) {
		ASTREE *declaration;
		declaration = node->son[0]->symbol->declaration;

		if(declaration->son[2]){
			//se a declaração tem só um parametro
			if(declaration->son[2]->type == AST_PARAMETRO) {
				if(!node->son[1]) {
					fprintf(stderr, "Erro: parametros de menos na funcao\n");
					exit(4);
				}
				else if(node->son[1]->type == AST_LISTA_PARAM_CHAMADA) {
					fprintf(stderr, "Erro: Parametros demais na chamada da funcao\n");
					exit(4);
				}

				checkParameterCompatibility(node->son[1]->dataType,declaration->son[2]->son[1]->dataType);
			}
			//se a declaração tem dois ou mais parametros
			else if(declaration->son[2]->type == AST_LISTA_PARAMETRO) {
				ASTREE *declarationParam = declaration->son[2];
				ASTREE *callParam = node->son[1];

				//if(!callParam->son[0]) exit(4);
				//checkParameterCompatibility(declarationParam->son[0]->dataType, callParam->son[0]->dataType);
			}
		}
		//se a declaração não tem parametro
		else {
			if(node->son[1]) {
				fprintf(stderr, "Erro: Parametros demais na chamada da funcao\n");
				exit(4);
			}
		}
	}

	for(i=0;i<MAX_SONS;i++) {
		checkFunctionParameters(node->son[i]);
	}		
}

int setTypesToAttrAndOperations(ASTREE* node) {
	int i;
	if(node==0) return DT_UNDEFINED;
	int type0;
	int type1;

	if(node->dataType == DT_UNDEFINED || node->type == AST_FUNCAO) {
		for(i=0;i<MAX_SONS;i++) {
			setTypesToAttrAndOperations(node->son[i]);
		}
	}
	else if(node->dataType == DT_NOT_SET || !node->dataType || node->dataType == DT_INT || node->dataType == DT_BOOL || node->dataType == DT_CHAR || node->dataType == DT_REAL) {
		switch(node->type) {
			case AST_OP_SOMA:
			case AST_OP_SUB:
			case AST_OP_MUL:
			case AST_OP_MENOR:
			case AST_OP_MAIOR:
			case AST_OP_LE:
			case AST_OP_GE:
			case AST_OP_EQ:
			case AST_OP_NE:
			case AST_OP_AND:
			case AST_OP_OR:
				 type0 = setTypesToAttrAndOperations(node->son[0]);
				 type1 = setTypesToAttrAndOperations(node->son[1]);			 
				 node->dataType = getDominantType(type0, type1, 0);
				 return node->dataType;
			case AST_OP_DIV:
				 type0 = setTypesToAttrAndOperations(node->son[0]);
				 type1 = setTypesToAttrAndOperations(node->son[1]);			 
				 node->dataType = getDominantType(type0, type1, 1);
				 return node->dataType;
			case AST_ATRIBUICAO:
				 type0 = node->son[0]->dataType;
				 type1 = setTypesToAttrAndOperations(node->son[1]);
				 node->dataType = getDominantType(type0, type1, 0);
				 return node->dataType;
	  	 	case AST_ATRIBUICAO_VETOR:
  	 			type0 = node->son[0]->dataType;
				type1 = setTypesToAttrAndOperations(node->son[1]);
				if(type1 == DT_BOOL || type1 == DT_REAL){
					fprintf(stderr, "Error: erro de tipo no acesso a uma posicao de vetor\n");
					exit(4);
				}
				type1 = setTypesToAttrAndOperations(node->son[2]);
				node->dataType = getDominantType(type0, type1);
				return node->dataType;
			default:
		 		return node->dataType;
	  }
	}
 	else{
	  for(i=0;i<MAX_SONS;i++) {
			setTypesToAttrAndOperations(node->son[i]);
	  }  
 	}
}