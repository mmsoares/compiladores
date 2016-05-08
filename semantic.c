#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"
#include "semantic.h"

void performSemanticValidations(HASH_NODE* hashmap, ASTREE* syntaxtree) {
	fprintf(stderr, "going to set the nature\n");
	setNature(syntaxtree);
	fprintf(stderr, "going to check declarations\n");
	checkDeclaration(syntaxtree);
	fprintf(stderr, "going to check identifiers usage\n");
	checkUsage(syntaxtree);	
	fprintf(stderr, "going to check types\n");
	checkType(syntaxtree);
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