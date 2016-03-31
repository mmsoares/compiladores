%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define YYDEBUG 0
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
 
%token TOKEN_ERROR  290

%token <symbol> LIT_INT
%token <symbol> LIT_REAL
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

variavel: tipo TK_IDENTIFIER ':' literal;

vetor: tipo TK_IDENTIFIER '[' LIT_INT ']'
     | tipo TK_IDENTIFIER '[' LIT_INT ']' ':' inicializacaovetor
     ;

inicializacaovetor: literal listaliterais;

listaliterais: literal listaliterais
	     |
             ;

funcao: tipo TK_IDENTIFIER '(' parametros ')' comando;

parametro: tipo TK_IDENTIFIER
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

comandos:	comando comandos
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

parametroschamada: listaparametroschamada
				|				
				;
				
listaparametroschamada: expressao ',' listaparametroschamada
		      | expressao
		      ;

restodalistadeparametroschamada: ',' parametroschamada
                        |
                        ;

expressao:	TK_IDENTIFIER
		| TK_IDENTIFIER '[' expressao ']'
		| TK_IDENTIFIER '(' parametroschamada ')'
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
		
atribuicao: TK_IDENTIFIER '=' expressao
			|	TK_IDENTIFIER'[' expressao ']' '=' expressao
		;
		
controlefluxo:	KW_IF '(' expressao ')' comando
				| KW_IF '(' expressao ')' comando KW_ELSE comando
				| KW_WHILE '(' expressao ')' comando
				;

input: KW_INPUT listadevariaveis
		;
		
listadevariaveis: TK_IDENTIFIER restolistadevariaveis
						;

restolistadevariaveis:  ',' listadevariaveis
                        |
                        ; 
                        
output: 	KW_OUTPUT listadeelementos
		;		

listadeelementos: expressao restolistadeelementos
						|	LIT_STRING restolistadeelementos
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

literal: LIT_INT
	   | LIT_REAL
       | LIT_TRUE
       | LIT_FALSE
       | LIT_CHAR
       | LIT_STRING
       ;


%%
int yyerror(char* str)
{
	fflush(stderr);
	fprintf(stderr,"Erro na linha: %d\n", getLineNumber());
	exit(3);
}

