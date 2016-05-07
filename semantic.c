#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"
#include "semantic.h"

void performSemanticValidations(struct hash_node_struct* hashmap, struct astree_struct* syntaxtree) {
	fprintf(stderr, "going to check declarations\n");
	checkDeclaration(syntaxtree);
	fprintf(stderr, "going to check for Undeclared variables\n");
	checkUndeclaredVariables(hashmap);
	fprintf(stderr, "going to check types\n");
	checkTypes(syntaxtree);
}

void checkDeclaration(struct astree_struct* syntaxtree) {
	struct astree_struct* declaration;
	struct astree_struct* declarations = syntaxtree->son[0];
	//struct astree_struct* declaration;

	//asTreePrintNodeWithDirectChildren(declarations->son[0]);
	for(declaration=declarations->son[1];declaration;declaration=declaration->son[1]) {
		//asTreePrintNodeWithDirectChildren(declaration);
	}

/*
	fprintf(stderr, "starting checkDeclaration\n");

	for (program = syntaxtree; program; program = program->son[0]) {
		fprintf(stderr, "starting for loop\n");
		declaration = program->son[1];
		type = declaration->son[0];
		identifier = declaration->son[1];

		fprintf(stderr, "set variables\n");

		if (identifier->symbol->type != SYMBOL_IDENTIFIER) {
			fprintf(stderr, "Erro: %s ja foi declarada.\n", identifier->symbol->text);
			exit(4);
		}

		fprintf(stderr, "checked if variable was already declared\n");

		identifier->symbol->declaration = declaration;

		switch (declaration->type) {
			case AST_VARIAVEL :
				identifier->symbol->type = SYMBOL_VARIABLE;
				break;
			case AST_VETOR_VAZIO:
			case AST_VETOR:
				identifier->symbol->type = SYMBOL_VECTOR;
				break;			
			case AST_FUNCAO :
				identifier->symbol->type = SYMBOL_FUNCTION;
				checkParameterDeclaration(declaration->son[2]);
				break;
			default:
				fprintf(stderr, "Erro: declaracao de tipo desconhecido");
				exit(4);
		}
		identifier->dataType = identifier->symbol->dataType;
		identifier->nature = identifier->symbol->type;
		declaration->symbol = identifier->symbol;
		declaration->dataType = identifier->dataType;
		declaration->nature = identifier->type;
	}
	*/
}

void checkParameterDeclaration(struct astree_struct* parameterList) {
/*	struct astree_struct* parameter;
	struct astree_struct* type;
	struct astree_struct* identifier;
	for (; list; list = list->son[1]) {
		parameter = list->son[0];
		type = parameter->son[0];
		identifier = parameter->son[1];
		if (identifier->symbol->type != TK_IDENTIFIER) {
			printf("SEMANTIC ERROR: Parameter %s already declared.\n", identifier->symbol->text);
			exit(4);
		} else {
			identifier->symbol->type = SYMBOL_FUNCTION_PARAM;
			parameter->dataType = identifier->symbol->dataType;
			parameter->nature = identifier->symbol->type;
		}
	}
	*/
}

void checkUndeclaredVariables(struct hash_node_struct* hashmap) {
	/*
	int index;
	struct hash_node_struct* node;
	for (index = 0; index < hashmap->size; ++index) {
		for (node = hashmap->entries[index]; node != NULL; node = node->next) {
			if (node->type == SYMBOL_IDENTIFIER) {
				printf("SEMANTIC ERROR: Undeclared variable %s.\n", node->text);
				exit(4);
			}
		}
	}
	*/
}

void checkTypes(struct astree_struct* syntaxtree) {
	/*
	for (; list; list = list->son[0]) {
		if (list->son[1]->type == FUNCTION_DECLARATION) {
			checkCodeType(list->son[1]->son[0], list->son[1]->son[1], list->son[1]->son[3]);
		}
	}
	*/
}

void checkCodeType(struct astree_struct* functionType, struct astree_struct* functionName, struct astree_struct* node) {
	
	/*struct astree_struct* list;
	switch (node->type) {
		case BLOCK :
			for (list = node->son[0]; list; list = list->son[1]) {
				if (list->son[0]) {
					checkCodeType(functionType, functionName, list->son[0]);
				}
			}
			break;
		case TYPE_BYTE :
			node->dataType = DATATYPE_BYTE;
			break;
		case TYPE_WORD :
			node->dataType = DATATYPE_WORD;
			break;
		case TYPE_BOOL :
			node->dataType = DATATYPE_BOOL;
			break;
		case SYMBOL :
			node->dataType = node->symbol->dataType;
			node->nature = node->symbol->type;
			break;
		case ADDRESS :
			checkCodeType(functionType, functionName, node->son[0]);
			node->dataType = DATATYPE_WORD;
			node->nature = SYMBOL_LITERAL_INTEGER;
			break;
		case POINTER :
			checkCodeType(functionType, functionName, node->son[0]);
			if (node->son[0]->symbol->type == SYMBOL_FUNCTION) {
				printf("SEMANTIC ERROR: Using function as pointer in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->son[0]->symbol->type == SYMBOL_VECTOR) {
				printf("SEMANTIC ERROR: Using vector as pointer in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->son[0]->symbol->type == SYMBOL_VARIABLE) {
				printf("SEMANTIC ERROR: Using variable as pointer in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			node->dataType = node->son[0]->symbol->dataType;
			node->nature = node->son[0]->symbol->type;
			break;
		case VECTOR :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			if (node->son[0]->symbol->type == SYMBOL_VARIABLE) {
				printf("SEMANTIC ERROR: Using non-vector as vector in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->son[0]->symbol->type == SYMBOL_FUNCTION) {
				printf("SEMANTIC ERROR: Using non-vector as vector in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->son[0]->symbol->type == SYMBOL_POINTER) {
				printf("SEMANTIC ERROR: Using non-vector as vector in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if ((node->son[1]->dataType == DATATYPE_BOOL) || (node->son[0]->symbol->type == SYMBOL_POINTER)) {
				printf("SEMANTIC ERROR: Using vector with invalid index in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			node->dataType = node->son[0]->dataType;
			node->nature = node->son[0]->nature;
			break;
		case FUNCTION_CALL :
			if ((node->son[0]->symbol->type == SYMBOL_VARIABLE) || (node->son[0]->symbol->type == SYMBOL_POINTER)){
				printf("SEMANTIC ERROR: Calling a non-function in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			{
				struct astree_struct* parameterlist;
				struct astree_struct* argumentlist;
				parameterlist = node->son[0]->symbol->declaration->son[2];
				argumentlist = node->son[1];
				while (parameterlist && argumentlist) {
					checkCodeType(functionType, functionName, argumentlist->son[0]);
					if (parameterlist->son[0]->dataType != argumentlist->son[0]->dataType) {
						if ((parameterlist->son[0]->dataType == DATATYPE_BOOL) && (argumentlist->son[0]->dataType != DATATYPE_BOOL)) {
							printf("SEMANTIC ERROR: Argument types mismatch when calling a function in function %s.\n", functionName->symbol->text);
							exit(4);
						}
						if ((parameterlist->son[0]->dataType != DATATYPE_BOOL) && (argumentlist->son[0]->dataType == DATATYPE_BOOL)) {
							printf("SEMANTIC ERROR: Argument types mismatch when calling a function in function %s.\n", functionName->symbol->text);
							exit(4);
						}
					}
					parameterlist = parameterlist->son[1];
					argumentlist = argumentlist->son[1];
				}
				if (parameterlist) {
					printf("SEMANTIC ERROR: Too few arguments when calling a function in function %s.\n", functionName->symbol->text);
					exit(4);
				}
				if (argumentlist) {
					printf("SEMANTIC ERROR: Too many arguments when calling a function in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			node->dataType = node->son[0]->symbol->dataType;
			node->nature = node->son[0]->symbol->type;
			break;
		case ASSIGN_VAR :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			if (node->son[0]->dataType != node->son[1]->dataType) {
				if ((node->son[0]->dataType == DATATYPE_BOOL) && (node->son[1]->dataType != DATATYPE_BOOL)) {
					printf("SEMANTIC ERROR: Invalid assignment using boolean types in function %s.\n", functionName->symbol->text);
					exit(4);
				}
				if ((node->son[0]->dataType != DATATYPE_BOOL) && (node->son[1]->dataType == DATATYPE_BOOL)) {
					printf("SEMANTIC ERROR: Invalid assignment using boolean types in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			if (node->son[1]->type == SYMBOL) {
				if ((node->son[0]->symbol->type == SYMBOL_LITERAL_STRING) || (node->son[1]->symbol->type == SYMBOL_LITERAL_STRING)) {
					printf("SEMANTIC ERROR: Invalid assignment using string in function %s.\n", functionName->symbol->text);
					exit(4);
				}
				if ((node->son[0]->type != SYMBOL_POINTER) && (node->son[1]->symbol->type == SYMBOL_POINTER)) {
					printf("SEMANTIC ERROR: Invalid assignment using pointer in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			break;
		case ASSIGN_VECTOR :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			checkCodeType(functionType, functionName, node->son[2]);
			if ((node->son[1]->dataType == DATATYPE_BOOL) || (node->son[0]->symbol->type == SYMBOL_POINTER)) {
				printf("SEMANTIC ERROR: Using vector with invalid index in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->son[0]->dataType != node->son[2]->dataType) {
				if ((node->son[0]->dataType == DATATYPE_BOOL) && (node->son[2]->dataType != DATATYPE_BOOL)) {
					printf("SEMANTIC ERROR: Invalid assignment using boolean types in function %s.\n", functionName->symbol->text);
					exit(4);
				}
				if ((node->son[0]->dataType != DATATYPE_BOOL) && (node->son[2]->dataType == DATATYPE_BOOL)) {
					printf("SEMANTIC ERROR: Invalid assignment using boolean types in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			if (node->son[2]->type == SYMBOL) {
				if ((node->son[0]->symbol->type == SYMBOL_LITERAL_STRING) || (node->son[2]->symbol->type == SYMBOL_LITERAL_STRING)) {
					printf("SEMANTIC ERROR: Invalid assignment using string in function %s.\n", functionName->symbol->text);
					exit(4);
				}
				if ((node->son[0]->symbol->type != SYMBOL_POINTER) && (node->son[2]->symbol->type == SYMBOL_POINTER)) {
					printf("SEMANTIC ERROR: Invalid assignment using pointer in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			break;
		case INPUT :
			checkCodeType(functionType, functionName, node->son[0]);
			break;
		case OUTPUT :
			checkCodeType(functionType, functionName, node->son[0]);
			if ((node->son[0]->dataType != DATATYPE_BYTE) && (node->son[0]->dataType != DATATYPE_WORD) && (node->son[0]->dataType != DATATYPE_BOOL)) {
				if ((node->son[0]->symbol != NULL) && (node->son[0]->symbol->type != LIT_STRING)) {
					printf("SEMANTIC ERROR: Invalid output in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			if ((node->son[0]->type != SYMBOL_VECTOR) && (node->son[1])) {
				printf("SEMANTIC ERROR: Using non-vector as vector in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if ((node->son[0]->type == SYMBOL_VECTOR) && (!node->son[1])) {
				printf("SEMANTIC ERROR: Using vector without index in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if ((node->son[0]->type == SYMBOL_VECTOR) && (node->son[1])) {
				if ((node->son[1]->dataType != DATATYPE_BYTE) && (node->son[1]->dataType != DATATYPE_WORD)) {
					printf("SEMANTIC ERROR: Invalid vector index in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			break;
		case OUTPUT_LIST :
			if (node->son[0]) {
				checkCodeType(functionType, functionName, node->son[0]);
			}
			if (node->son[1]) {
				checkCodeType(functionType, functionName, node->son[1]);
			}
			node->dataType = node->son[0]->dataType;
			node->nature = node->son[0]->type;
			break;
		case RETURN :
			checkCodeType(functionType, functionName, node->son[0]);
			if (node->son[0]->dataType != functionName->dataType) {
				printf("SEMANTIC ERROR: Return type does not match function type in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			break;
		case IF_THEN :
		case IF_ELSE :
		case IF_LOOP :
			checkCodeType(functionType, functionName, node->son[0]);
			if (node->son[1]) {
				checkCodeType(functionType, functionName, node->son[1]);
			}
			if (node->son[2]) {
				checkCodeType(functionType, functionName, node->son[2]);
			}
			if (node->son[3]) {
				checkCodeType(functionType, functionName, node->son[3]);
			}
			if (node->son[0]->dataType != DATATYPE_BOOL) {
				printf("SEMANTIC ERROR: If with non-boolean condition in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			break;
		case EXPRESSION_ORDER :
			checkCodeType(functionType, functionName, node->son[0]);
			node->dataType = node->son[0]->dataType;
			node->nature = node->son[0]->nature;
			break;
		case OP_PLUS :
		case OP_MINUS :
		case OP_TIMES :
		case OP_DIVIDE :
		case OP_MODULE :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			if (node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL) {
				printf("SEMANTIC ERROR: Invalid arithmetic operation using boolean in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->son[0]->nature == SYMBOL_LITERAL_STRING || node->son[1]->nature == SYMBOL_LITERAL_STRING) {
				printf("SEMANTIC ERROR: Invalid arithmetic operation using string in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if (node->type == OP_PLUS) {
				if (node->son[0]->nature == SYMBOL_POINTER && node->son[1]->nature == SYMBOL_POINTER) {
					printf("SEMANTIC ERROR: Invalid arithmetic operation using only pointer in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			} else {
				if (node->son[0]->nature == SYMBOL_POINTER || node->son[1]->nature == SYMBOL_POINTER) {
					printf("SEMANTIC ERROR: Invalid arithmetic operation using pointer in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			if (node->son[0]->dataType == DATATYPE_WORD || node->son[1]->dataType == DATATYPE_WORD) {
				node->dataType = DATATYPE_WORD;
			} else {
				node->dataType = DATATYPE_BYTE;
			}
			if (node->son[0]->nature == SYMBOL_POINTER || node->son[1]->nature == SYMBOL_POINTER) {
				node->nature = SYMBOL_POINTER;
			} else {
				if (node->son[0]->nature == SYMBOL_LITERAL_INTEGER || node->son[1]->nature == SYMBOL_LITERAL_INTEGER) {
					node->nature = SYMBOL_LITERAL_INTEGER;
				} else {
					node->nature = SYMBOL_LITERAL_CHAR;
				}
			}
			break;
		case OP_LESSER :
		case OP_GREATER :
		case OP_LESSEREQUAL :
		case OP_GREATEREQUAL :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			if ((node->son[0]->dataType != DATATYPE_BYTE) && (node->son[0]->dataType != DATATYPE_WORD)) {
				printf("SEMANTIC ERROR: Invalid first operator of logic operation in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			if ((node->son[1]->dataType != DATATYPE_WORD) && (node->son[1]->dataType != DATATYPE_BYTE)) {
				printf("SEMANTIC ERROR: Invalid second operator of logic operation in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			node->dataType = DATATYPE_BOOL;
			node->nature = SYMBOL_BOOLEAN;
			break;
		case OP_EQUAL :
		case OP_NOTEQUAL :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			if (node->son[0]->dataType != node->son[1]->dataType) {
				if ((node->son[0]->dataType == DATATYPE_BOOL) && (node->son[1]->dataType != DATATYPE_BOOL)) {
					printf("SEMANTIC ERROR: Invalid logic operation in function %s.\n", functionName->symbol->text);
					exit(4);
				}
				if ((node->son[0]->dataType != DATATYPE_BOOL) && (node->son[1]->dataType == DATATYPE_BOOL)) {
					printf("SEMANTIC ERROR: Invalid logic operation in function %s.\n", functionName->symbol->text);
					exit(4);
				}
			}
			node->dataType = DATATYPE_BOOL;
			node->nature = SYMBOL_BOOLEAN;
			break;
		case OP_AND :
		case OP_OR :
			checkCodeType(functionType, functionName, node->son[0]);
			checkCodeType(functionType, functionName, node->son[1]);
			if ((node->son[0]->dataType != DATATYPE_BOOL) || (node->son[1]->dataType != DATATYPE_BOOL)) {
				printf("SEMANTIC ERROR: Invalid logic operation in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			node->dataType = DATATYPE_BOOL;
			node->nature = SYMBOL_BOOLEAN;
			break;
		case OP_NOT :
			checkCodeType(functionType, functionName, node->son[0]);
			if (node->son[0]->dataType != DATATYPE_BOOL) {
				printf("SEMANTIC ERROR: Invalid logic operation with in function %s.\n", functionName->symbol->text);
				exit(4);
			}
			node->dataType = DATATYPE_BOOL;
			node->nature = SYMBOL_BOOLEAN;
			break;
		default:
			printf("SEMANTIC ERROR: Unknown node of type %d in function %s.\n", node->type, functionName->symbol->text);
			exit(4);
			break;
	}
	*/
}