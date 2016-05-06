#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"

extern  int     getLineNumber(void);
//extern  FILE    *outputFile;

ASTREE* astreeCreate(int type, HASH_NODE *symbol, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3) {
	ASTREE *newnode = 0;
	newnode = (ASTREE*) calloc(1,sizeof(ASTREE));
	newnode->symbol = symbol;
	newnode->type = type;
   newnode->nature = NATURE_UNDEFINED;
   newnode->dataType = DT_UNDEFINED;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;


	return newnode;
}

void defineDataType(struct hash_node_struct *symbol, int type) {
	fprintf(stderr, "setting data type %d for symbol %s\n", type, symbol->text);
	if(symbol->dataType == DT_UNDEFINED) {
		switch(type) {
			case AST_KW_INT:
				symbol->dataType = DT_INT;
				break;
			case AST_KW_BOOL:
				symbol->dataType = DT_BOOL;
				break;
			case AST_KW_CHAR:
				symbol->dataType = DT_CHAR;				
				break;
			case AST_KW_REAL:
				symbol->dataType = DT_REAL;				
				break;
			default: break;
		}
	}
}

void astreePrint(ASTREE* node, int level) {
	int i;

	if(node==0) return;

	for(i=0;i<level; ++i) fprintf(stderr, "  ");
	//fprintf(stderr, "Astree(");

	switch(node->type) {
		case AST_PROGRAMA: 		fprintf(stderr,"AST_PROGRAMA"); break;
		case AST_DECLARACOES:   fprintf(stderr, "DECLARACOES"); break;
		case AST_VARIAVEL: 		fprintf(stderr,"AST_VARIAVEL"); break;
		case AST_VETOR_VAZIO: 		fprintf(stderr,"AST_VETOR_VAZIO"); break;
		case AST_VETOR: 		fprintf(stderr,"AST_VETOR"); break;
		case AST_INI_VETOR: 		fprintf(stderr,"AST_INI_VETOR"); break;
		case AST_LISTA_LITERAIS: 	fprintf(stderr,"AST_LISTA_LITERAIS"); break;
		case AST_FUNCAO: 		fprintf(stderr,"AST_FUNCAO"); break;
		case AST_PARAMETRO: 		fprintf(stderr,"AST_PARAMETRO"); break;
		case AST_LISTA_PARAMETRO: 	fprintf(stderr,"AST_LISTA_PARAMETRO"); break;
		case AST_COMANDOS: 		fprintf(stderr,"AST_COMANDOS"); break;
		case AST_LISTA_PARAM_CHAMADA: 	fprintf(stderr,"AST_LISTA_PARAM_CHAMADA"); break;
		case AST_ACESSO_VETOR: 		fprintf(stderr,"AST_ACESSO_VETOR"); break;
		case AST_CHAMADA_FUNCAO: 	fprintf(stderr,"AST_CHAMADA_FUNCAO"); break;
		case AST_OP_SOMA: 		fprintf(stderr,"AST_OP_SOMA"); break;
		case AST_OP_SUB: 		fprintf(stderr,"AST_OP_SUB"); break;
		case AST_OP_MUL: 		fprintf(stderr,"AST_OP_MUL"); break;
		case AST_OP_DIV: 		fprintf(stderr,"AST_OP_DIV"); break;
		case AST_OP_MENOR: 		fprintf(stderr,"AST_OP_MENOR"); break;
		case AST_OP_MAIOR: 		fprintf(stderr,"AST_OP_MAIOR"); break;
		case AST_OP_LE: 		fprintf(stderr,"AST_OP_LE"); break;
		case AST_OP_GE: 		fprintf(stderr,"AST_OP_GE"); break;
		case AST_OP_EQ: 		fprintf(stderr,"AST_OP_EQ"); break;
		case AST_OP_NE: 		fprintf(stderr,"AST_OP_NE"); break;
		case AST_OP_AND: 		fprintf(stderr,"AST_OP_AND"); break;
		case AST_OP_OR: 		fprintf(stderr,"AST_OP_OR"); break;
		case AST_ATRIBUICAO: 		fprintf(stderr,"AST_ATRIBUICAO"); break;
		case AST_ATRIBUICAO_VETOR: 	fprintf(stderr,"AST_ATRIBUICAO_VETOR"); break;
		case AST_IF: 			fprintf(stderr,"AST_IF"); break;
		case AST_IF_ELSE: 		fprintf(stderr,"AST_IF_ELSE"); break;
		case AST_WHILE: 		fprintf(stderr,"AST_WHILE"); break;
		case AST_INPUT: 		fprintf(stderr,"AST_INPUT"); break;
		case AST_LISTA_VARIAVEIS: 	fprintf(stderr,"AST_LISTA_VARIAVEIS"); break;
		case AST_OUTPUT: 		fprintf(stderr,"AST_OUTPUT"); break;
		case AST_LISTA_ELEM_EXP: 	fprintf(stderr,"AST_LISTA_ELEM_EXP"); break;
		case AST_LISTA_ELEM_STRING: 	fprintf(stderr,"AST_LISTA_ELEM_STRING"); break;
		case AST_RETURN: 		fprintf(stderr,"AST_RETURN"); break;
		case AST_KW_INT: 		fprintf(stderr,"AST_KW_INT"); break;
		case AST_KW_BOOL: 		fprintf(stderr,"AST_KW_BOOL"); break;
		case AST_KW_REAL: 		fprintf(stderr,"AST_KW_REAL"); break;
		case AST_KW_CHAR: 		fprintf(stderr,"AST_KW_CHAR"); break;
		case AST_LIT_INT: 		fprintf(stderr,"AST_LIT_INT"); break;
		case AST_LIT_REAL: 		fprintf(stderr,"AST_LIT_REAL"); break;
		case AST_LIT_TRUE: 		fprintf(stderr,"AST_LIT_TRUE"); break;
		case AST_LIT_FALSE: 	fprintf(stderr,"AST_LIT_FALSE"); break;
		case AST_LIT_CHAR: 		fprintf(stderr,"AST_LIT_CHAR"); break;
		case AST_LIT_STRING: 	fprintf(stderr,"AST_LIT_STRING"); break;
		case AST_BLOCO:			fprintf(stderr,"AST_BLOCO"); break;
		case AST_IDENTIFIER:    fprintf(stderr, "AST_IDENTIFIER"); break;
		case AST_COMANDO_VAZIO:    fprintf(stderr, "AST_COMANDO_VAZIO"); break;
      case AST_SYMBOL:  fprintf(stderr, "AST_SYMBOL"); break;

		default: fprintf(stderr, "UNKNOWN"); 
				 fprintf(stderr, "Node type: %d\n", node->type);
				 break;
	}
	if(node->symbol) {
		fprintf(stderr, ",%s", node->symbol->text);
		fprintf(stderr, ", %d", node->symbol->dataType);
	}

	fprintf(stderr, "\n");
	
	for(i=0;i<MAX_SONS;i++) {
		astreePrint(node->son[i], level+1);
	}
}
/*
void decompile(ASTREE *raiz) {
	
	if (raiz !=0)
	{
	    switch(raiz->type)
	    {	
			case AST_PROGRAMA:	
				decompile(raiz->son[0]);
				break;

			case AST_DECLARACOES:
				decompile(raiz->son[0]);
				fprintf(outputFile, " ; ");
				decompile(raiz->son[1]);
				break;
		
			case AST_VARIAVEL:	
				decompile(raiz->son[0]);
				fprintf(outputFile," %s : ",raiz->symbol->text);  
                		decompile(raiz->son[1]); 
				break;
					
			case AST_VETOR_VAZIO:	
				decompile(raiz->son[0]);
				fprintf(outputFile," %s [ ",raiz->symbol->text);  
                		decompile(raiz->son[1]);
				fprintf(outputFile,"]"); 
				break;				
			
			case AST_VETOR:		
				decompile(raiz->son[0]);
				fprintf(outputFile," %s [ ",raiz->symbol->text);  
                		decompile(raiz->son[1]);
				fprintf(outputFile," ]: ");
				decompile(raiz->son[2]); 
				break;				
			
			case AST_INI_VETOR: 	 
				decompile(raiz->son[0]);
				decompile(raiz->son[1]); 
				break;

			case AST_LISTA_LITERAIS:
				decompile(raiz->son[0]);
				decompile(raiz->son[1]); 
				break;
			
			case AST_FUNCAO:
				decompile(raiz->son[0]);
				fprintf(outputFile," %s ( ",raiz->symbol->text);  
				decompile(raiz->son[1]);
				fprintf(outputFile," ) ");
				decompile(raiz->son[2]);
				break;

			case AST_PARAMETRO:
				decompile(raiz->son[0]);
				fprintf(outputFile," %s ",raiz->symbol->text);
				break;

			case AST_LISTA_PARAMETRO:
				decompile(raiz->son[0]);
				fprintf(outputFile,",");
				decompile(raiz->son[1]);
				break;

			case AST_COMANDOS:
				decompile(raiz->son[0]);
				decompile(raiz->son[1]);
				break;
			
			case AST_COMANDO_VAZIO:
				fprintf(outputFile," ; ");
				break;
				
			case AST_BLOCO:
				fprintf(outputFile," { ");
				decompile(raiz->son[0]);
				fprintf(outputFile," } ");
				break;
			
			case AST_LISTA_PARAM_CHAMADA:
				decompile(raiz->son[0]);
				fprintf(outputFile," , ");
				decompile(raiz->son[1]);
				break;
			
			case AST_ACESSO_VETOR:
				fprintf(outputFile," %s [ ",raiz->symbol->text);				
				decompile(raiz->son[0]);
				fprintf(outputFile,"]");
				break;
			
			case AST_CHAMADA_FUNCAO:
				fprintf(outputFile," %s ( ",raiz->symbol->text);				
				decompile(raiz->son[0]);
				fprintf(outputFile," ) ");
				break;

			case AST_OP_SOMA:
				decompile(raiz->son[0]);
				fprintf(outputFile," + ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_SUB:
				decompile(raiz->son[0]);
				fprintf(outputFile," - ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_MUL:
				decompile(raiz->son[0]);
				fprintf(outputFile," * ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_DIV:
				decompile(raiz->son[0]);
				fprintf(outputFile," / ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_MENOR:
				decompile(raiz->son[0]);
				fprintf(outputFile," < ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_MAIOR:
				decompile(raiz->son[0]);
				fprintf(outputFile," > ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_LE:
				decompile(raiz->son[0]);
				fprintf(outputFile," <= ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_GE:
				decompile(raiz->son[0]);
				fprintf(outputFile," >= ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_EQ:
				decompile(raiz->son[0]);
				fprintf(outputFile," == ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_NE:
				decompile(raiz->son[0]);
				fprintf(outputFile," != ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_AND:
				decompile(raiz->son[0]);
				fprintf(outputFile," && ");
				decompile(raiz->son[1]);
				break;

			case AST_OP_OR:
				decompile(raiz->son[0]);
				fprintf(outputFile," || ");
				decompile(raiz->son[1]);
				break;
			
			case AST_ATRIBUICAO:
				fprintf(outputFile," %s = ",raiz->symbol->text);
				decompile(raiz->son[0]);
				break;

			case AST_ATRIBUICAO_VETOR:
				fprintf(outputFile," %s [ ",raiz->symbol->text);
				decompile(raiz->son[0]);
				fprintf(outputFile," ] = ");
				decompile(raiz->son[1]);
				break;
			
			case AST_IF:
				fprintf(outputFile," if ( ");
				decompile(raiz->son[0]);
				fprintf(outputFile," ) ");
				decompile(raiz->son[1]);
				break;

			case AST_IF_ELSE:
				fprintf(outputFile," if ( ");
				decompile(raiz->son[0]);
				fprintf(outputFile," ) ");
				decompile(raiz->son[1]);
				fprintf(outputFile," else ");
				decompile(raiz->son[2]);
				break;

			case AST_WHILE:
				fprintf(outputFile," while ( ");
				decompile(raiz->son[0]);
				fprintf(outputFile," ) ");
				decompile(raiz->son[1]);
				break;

			case AST_INPUT:
				fprintf(outputFile," input ");
				decompile(raiz->son[0]);
				break;

			case AST_LISTA_VARIAVEIS:
				fprintf(outputFile," %s ",raiz->symbol->text);
				decompile(raiz->son[0]);
				break;
			
			case AST_OUTPUT:
				fprintf(outputFile," output ");
				decompile(raiz->son[0]);
				break;

			case AST_LISTA_ELEM_EXP:
				
				decompile(raiz->son[0]);
				if(raiz->son[1]){
					fprintf(outputFile," , ");
				}
				decompile(raiz->son[1]);
				
				break;

			case AST_LISTA_ELEM_STRING:
				fprintf(outputFile," \"%s\" ",raiz->symbol->text);
				if(raiz->son[0]){
					fprintf(outputFile," , ");
				}
				decompile(raiz->son[0]);
				break;

			case AST_RETURN:
				fprintf(outputFile," return ");
				decompile(raiz->son[0]);
				break;

			case AST_KW_BOOL:
				fprintf(outputFile," bool ");
				break;

			case AST_KW_REAL:
				fprintf(outputFile," real ");
				break;

			case AST_KW_CHAR:
				fprintf(outputFile," char ");
				break;

			case AST_KW_INT:
				fprintf(outputFile," int ");
				break;

			case AST_LIT_INT:
				fprintf(outputFile," %s ",raiz->symbol->text);
				break;

			case AST_LIT_REAL:
				fprintf(outputFile," %s ",raiz->symbol->text);
				break;

			case AST_LIT_TRUE:
				fprintf(outputFile," %s ",raiz->symbol->text);
				break;

			case AST_LIT_FALSE:
				fprintf(outputFile," %s ",raiz->symbol->text);
				break;

			case AST_LIT_CHAR:
				fprintf(outputFile," \'%s\' ",raiz->symbol->text);
				break;

			case AST_LIT_STRING:
				fprintf(outputFile," \"%s\" ",raiz->symbol->text);
				break;

			case AST_IDENTIFIER:
				fprintf(outputFile, " %s ", raiz->symbol->text);
				break;
			default:		 
				fprintf(stderr,"Fim da execucao do Decompile!"); 
				break;      
	    }
    }

}
*/
