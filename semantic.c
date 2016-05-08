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

int setTypes(ASTREE* node) {
	int i;

	if(node==0) return DT_UNDEFINED;

//

	int typeSon[MAX_SONS];
	for(i=0;i<MAX_SONS;i++) {
		typeSon[i] = setTypes(node->son[i]);
	}

	int type = DT_UNDEFINED;

	for(i=0;i<MAX_SONS; i++) {
		int typeSons = typeSon[i];

		if(typeSon[i] != DT_UNDEFINED) {
			if(type == DT_UNDEFINED) {
				type = typeSons;
			}
			else {

			}
		}
	}

	return type;
}

void checkTypes(ASTREE *node) {
	
}