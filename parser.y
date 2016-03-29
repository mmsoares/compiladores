%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define YYDEBUG 1
int yydebug = 1;

%}

%union {
	HASH_NODE *symbol;
}

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

%token <symbol> LIT_INTEGER
%token <symbol> LIT_FALSE
%token <symbol> LIT_TRUE
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING
%token <symbol> TK_IDENTIFIER

%left LIT_FALSE LIT_TRUE OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE '>' '<'  LIT_CHAR 
%left OPERATOR_OR
%left OPERATOR_AND
%left '+' '-'
%left '*' '/' 
%left ','
%left ')' ']' 
%nonassoc '!' '$' '&'

%%

programa: declaracao ';' programa
	     |
	     ;

declaracao: variavel
		  | vetor
		  | funcao
	      ;

variavel: tipo SYMBOL_IDENTIFIER ':' literal;

vetor: tipo SYMBOL_IDENTIFIER '[' SYMBOL_LIT_INT ']'
     | tipo SYMBOL_IDENTIFIER '[' SYMBOL_LIT_INT ']' ':' inicializacaovetor
     ;

inicializacaovetor: literal listaliterais;

listaliterais: literal listaliterais
	     |
             ;

funcao: tipo SYMBOL_IDENTIFIER '(' parametros ')' comando;

parametro: tipo SYMBOL_IDENTIFIER
         ;

parametros: listaparametros
				|				
				;
				
listaparametros: parametro ',' listaparametros
					| parametro
					;

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
		;
		
atribuicao: SYMBOL_IDENTIFIER '=' expressao
			|	SYMBOL_IDENTIFIER'[' expressao ']' '=' expressao
		;
		
controlefluxo:	KW_IF '(' expressao ')' comando
				| KW_IF '(' expressao ')' comando KW_ELSE comando
				| KW_WHILE '(' expressao ')' comando
				;

input: KW_INPUT listadevariaveis
		;
		
listadevariaveis: SYMBOL_IDENTIFIER restolistadevariaveis
						;

restolistadevariaveis:  ',' listadevariaveis
                        |
                        ; 
                        
output: 	KW_OUTPUT listadeelementos
		;		

listadeelementos: expressao restolistadeelementos
						|	SYMBOL_LIT_STRING restolistadeelementos
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
	fprintf(stderr,"Erro na linha: %d\n", getLineNumber());
	exit(3);
}

