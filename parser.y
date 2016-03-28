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

comandos:	comando ';' comandos
		| comando 
		| bloco
		;
		
comando: bloco
	   | atribuicao
	   | controlefluxo
	   | input
	   | output
	   | return
	   | ';'
	   ;

bloco: '{' comandos '}';

expressao:	SYMBOL_IDENTIFIER
		| SYMBOL_IDENTIFIER '[' expressao ']'
		| SYMBOL_IDENTIFIER '(' parametros ')'
		| literal
		| '(' expressao ')'
		| expressao '+' expressao
		| expressao '-' expressao
		| expressao '*' expressao
		| expressao '/' expressao
		| expressao '<' expressao
		| expressao '>' expressao
		| expressao OPERATOR_LE expressao
		| expressao OPERATOR_GE expressao
		| expressao OPERATOR_EQ expressao
		| expressao OPERATOR_NE expressao
		| expressao OPERATOR_AND expressao
		| expressao OPERATOR_OR expressao
		| '*' SYMBOL_IDENTIFIER	
		| '&' SYMBOL_IDENTIFIER
		;
		
atribuicao: SYMBOL_IDENTIFIER '=' expressao
			|	SYMBOL_IDENTIFIER'[' expressao ']' = expressao
		;
		
controlefluxo:	KW_IF expressao KW_LOOP comando
		| KW_IF expressao KW_LOOP comando
		| KW_IF expressao KW_THEN comando
		| KW_IF expressao KW_THEN comando KW_ELSE comando
		| KW_IF expressao KW_ELSE comando
		;

input: SYMBOL_IDENTIFIER listadevariaveis
		;
		
listadevariaveis: SYMBOL_IDENTIFIER restolistadevariaveis
;

restolistadevariaveis:  ',' listadevariaveis
                        |
                        ; 
                        
output: 	KW_OUTPUT listadeelementos
		;		

listadeelementos: expressao restolistadeelementos
						|	SYMBOL_IDENTIFIER restolistadeelementos
;

restolistadeelementos:  ',' listadeelementos
                        |
                        ; 

return: KW_RETURN expressao
		;


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

