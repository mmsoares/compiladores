%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

//#define YYDEBUG 1
//int yydebug = 1;
 
extern int getLineNumber(void);
extern int isRunning(void);

#define SYMBOL_LIT_INT    1;
#define SYMBOL_LIT_REAL   2;
#define SYMBOL_LIT_FALSE  3;
#define SYMBOL_LIT_TRUE   4;
#define SYMBOL_LIT_CHAR   5;
#define SYMBOL_LIT_STRING 6;
#define SYMBOL_IDENTIFIER 7;
 
%}

%token KW_INT		256
%token KW_REAL		258
%token KW_BOOL		259
%token KW_CHAR		261
%token KW_IF		262
%token KW_ELSE		263
%token KW_WHILE		264
%token KW_INPUT		266
%token KW_RETURN	267
%token KW_OUTPUT	268
 
%token OPERATOR_LE	270
%token OPERATOR_GE	271
%token OPERATOR_EQ	272
%token OPERATOR_NE	273
%token OPERATOR_AND	274
%token OPERATOR_OR	275
 
%token TOKEN_ERROR		290

%%

programa: declaracao ';' programa
	     |
	     ;

declaracao: variavel
		  | vetor
		  | funcao
	      ;

variavel: tipo SYMBOL_IDENTIFIER ':' literal;

vetor: tipo SYMBOL_IDENTIFIER '[' SYMBOL_LIT_INT ']' valoresvetor;

valoresvetor: ':' listadevalores
				  |  
				  ;

listadevalores: literal restodalistadevalores;

restodalistadevalores: ',' listadevalores
            		 |
            		 ;

funcao: tipo SYMBOL_IDENTIFIER '(' parametros ')' comando;

parametro: tipo literal
         |
         ;

parametros: parametro restodalistadeparametros;

restodalistadeparametros: ',' parametros
                        |
                        ;                 

comando: bloco
	   | atribuicao
	   | controlefluxo
	   | entrada
	   | saida
	   | retorno
	   | ';'
	   ;

bloco: '{' comando '}';

tipo: KW_INT
    | KW_BOOL
	| KW_REAL
	| KW_CHAR
	;

literal: SYMBOL_LIT_INT
	   | SYMBOL_LIT_REAL
       | SYMBOL_LIT_TRUE
       | SYMBOL_LIT_FALSE
       | SYMBOL_LIT_CHAR
       | SYMBOL_LIT_STRING
       ;


%%
int yyerror(char* str)
{
	fflush(stderr);
	fprintf(stderr,"Erro: \"%s\"\t na linha: %d\n", str, getLineNumber());
	exit(3);
}

