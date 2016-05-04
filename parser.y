%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"

#define YYDEBUG 0
int yydebug = 1;
%}

%union {
    ASTREE    *ast;  
    HASH_NODE *symbol;
}

%token KW_INT       256
%token KW_REAL      258
%token KW_BOOL      259
%token KW_CHAR      261
%token KW_IF        262
%token KW_ELSE      263
%token KW_WHILE     264
%token KW_INPUT     266
%token KW_RETURN    267
%token KW_OUTPUT    268


%token OPERATOR_LE  270
%token OPERATOR_GE  271
%token OPERATOR_EQ  272
%token OPERATOR_NE  273
%token OPERATOR_AND 274
%token OPERATOR_OR  275
 
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






%type <ast> programa
%type <ast> declaracoes
%type <ast> declaracao
%type <ast> variavel
%type <ast> vetor
%type <ast> inicializacaovetor
%type <ast> listaliterais
%type <ast> funcao
%type <ast> parametro
%type <ast> parametros
%type <ast> listaparametros
%type <ast> restodalistadeparametros
%type <ast> comandos
%type <ast> comando
%type <ast> bloco
%type <ast> parametroschamada
%type <ast> listaparametroschamada
%type <ast> restodalistadeparametroschamada
%type <ast> expressao
%type <ast> atribuicao
%type <ast> controlefluxo
%type <ast> input
%type <ast> listadevariaveis
%type <ast> restolistadevariaveis
%type <ast> output
%type <ast> listadeelementos
%type <ast> restolistadeelementos
%type <ast> return
%type <ast> tipo
%type <ast> literal


%start  programa

%%

programa: declaracoes     { 
            $$ = astreeCreate(AST_PROGRAMA,0,$1,0,0,0);
            astreePrint ($$,0);
            decompile($$);
              }
         |            {  $$=astreeCreate(AST_PROGRAMA,0,0,0,0,0); }
         ;

declaracoes: declaracao ';' declaracoes {$$=astreeCreate(AST_DECLARACOES,0,$1,$3,0,0);}
            |                           {$$=0;}
            ;

declaracao: variavel {$$=$1;}
          | vetor    {$$=$1;}
          | funcao   {$$=$1;}
          ;

variavel: tipo TK_IDENTIFIER ':' literal {$$ = astreeCreate(AST_VARIAVEL,$2,$1,$4,0,0);}
            ;

vetor: tipo TK_IDENTIFIER '[' LIT_INT ']'      {$$ = astreeCreate(AST_VETOR_VAZIO,$2,$1,astreeCreate(AST_LIT_INT,$4,0,0,0,0),0,0);}
     | tipo TK_IDENTIFIER '[' LIT_INT ']' ':' inicializacaovetor {$$ = astreeCreate(AST_VETOR,$2,$1,astreeCreate(AST_LIT_INT,$4,0,0,0,0),$7,0);}
     ;

inicializacaovetor: literal listaliterais   {$$ = astreeCreate(AST_INI_VETOR,0,$1,$2,0,0);}
    ; 

listaliterais: literal listaliterais    {$$ = astreeCreate(AST_LISTA_LITERAIS,0,$1,$2,0,0);}
         |                        {$$=0;}
             ;

funcao: tipo TK_IDENTIFIER '(' parametros ')' comando {$$ = astreeCreate(AST_FUNCAO,$2,$1,$4,$6,0);}
    ;  

parametro: tipo TK_IDENTIFIER   {$$ = astreeCreate(AST_PARAMETRO,$2,$1,0,0,0);}
         ;

parametros: listaparametros {$$=$1;}
                |               {$$=0;}
                ;
                
listaparametros: parametro ',' listaparametros {$$ = astreeCreate(AST_LISTA_PARAMETRO,0,$1,$3,0,0);}
                    | parametro          {$$=$1;}
                    ;

restodalistadeparametros: ',' parametros     {$$=$2;}
                        |                    {$$=0;}
                        ;                 

comandos:   comando comandos  {$$ = astreeCreate(AST_COMANDOS,0,$1,$2,0,0);}
            | comando     {$$=$1;}
            | bloco   {$$=$1;}
            ;
        
comando: bloco    {$$=$1;}
       | atribuicao {$$=$1;}
       | controlefluxo  {$$=$1;}
       | input    {$$=$1;}
       | output   {$$=$1;}
       | return   {$$=$1;}
       | ';'    {$$=astreeCreate(AST_COMANDO_VAZIO,0,0,0,0,0);}
       ;

bloco: '{' comandos '}'   {$$ = astreeCreate(AST_BLOCO,0,$2,0,0,0);}
  ;

parametroschamada: listaparametroschamada   {$$=$1;}
                |                           {$$=0;}
                ;
                
listaparametroschamada: expressao ',' listaparametroschamada  {$$ = astreeCreate(AST_LISTA_PARAM_CHAMADA,0,$1,$3,0,0);}
              | expressao         {$$=$1;}
              ;


restodalistadeparametroschamada: ',' parametroschamada  {$$=$2;}
                        |                                {$$=0;}
                        ;



expressao:  TK_IDENTIFIER       {$$ = astreeCreate(AST_IDENTIFIER,$1,0,0,0,0);}
        | TK_IDENTIFIER '[' expressao ']'   {$$ = astreeCreate(AST_ACESSO_VETOR,0,$1,$3,0,0);}
        | TK_IDENTIFIER '(' parametroschamada ')' {$$ = astreeCreate(AST_CHAMADA_FUNCAO,$1,$3,0,0,0);}
        | literal         {$$=$1;}
        | '(' expressao ')'       {$$ = astreeCreate(AST_EXPRESSAO_PARENTESES,0,$2,0,0,0);}
        | expressao '+' expressao     {$$ = astreeCreate(AST_OP_SOMA,0,$1,$3,0,0);}
        | expressao '-' expressao     {$$ = astreeCreate(AST_OP_SUB,0,$1,$3,0,0);}
        | expressao '*' expressao     {$$ = astreeCreate(AST_OP_MUL,0,$1,$3,0,0);}
        | expressao '/' expressao     {$$ = astreeCreate(AST_OP_DIV,0,$1,$3,0,0);}
        | expressao '<' expressao     {$$ = astreeCreate(AST_OP_MENOR,0,$1,$3,0,0);}
        | expressao '>' expressao     {$$ = astreeCreate(AST_OP_MAIOR,0,$1,$3,0,0);}
        | expressao OPERATOR_LE expressao   {$$ = astreeCreate(AST_OP_LE,0,$1,$3,0,0);}
        | expressao OPERATOR_GE expressao   {$$ = astreeCreate(AST_OP_GE,0,$1,$3,0,0);}
        | expressao OPERATOR_EQ expressao   {$$ = astreeCreate(AST_OP_EQ,0,$1,$3,0,0);}
        | expressao OPERATOR_NE expressao   {$$ = astreeCreate(AST_OP_NE,0,$1,$3,0,0);}
        | expressao OPERATOR_AND expressao    {$$ = astreeCreate(AST_OP_AND,0,$1,$3,0,0);}
        | expressao OPERATOR_OR expressao   {$$ = astreeCreate(AST_OP_OR,0,$1,$3,0,0);}
        ;

        

atribuicao: TK_IDENTIFIER '=' expressao       {$$ = astreeCreate(AST_ATRIBUICAO,$1,$3,0,0,0);}
            |   TK_IDENTIFIER'[' expressao ']' '=' expressao  {$$ = astreeCreate(AST_ATRIBUICAO_VETOR,$1,$3,$6,0,0);}
        ;

        

controlefluxo:  KW_IF '(' expressao ')' comando       {$$ = astreeCreate(AST_IF,0,$3,$5,0,0);}
                | KW_IF '(' expressao ')' comando KW_ELSE comando {$$ = astreeCreate(AST_IF_ELSE,0,$3,$5,$7,0);}
                | KW_WHILE '(' expressao ')' comando      {$$ = astreeCreate(AST_WHILE,0,$3,$5,0,0);}
                ;



input: KW_INPUT listadevariaveis  {$$ = astreeCreate(AST_INPUT,0,$2,0,0,0);}
        ;

        

listadevariaveis: TK_IDENTIFIER restolistadevariaveis {$$ = astreeCreate(AST_LISTA_VARIAVEIS,$1,$2,0,0,0);}
                        ;



restolistadevariaveis:  ',' listadevariaveis  {$$=$2;}
                        |                     {$$=0;}
                        ; 

                        

output:     KW_OUTPUT listadeelementos  {$$ = astreeCreate(AST_OUTPUT,0,$2,0,0,0);}
        ;       

listadeelementos: expressao restolistadeelementos   {$$ = astreeCreate(AST_LISTA_ELEM_EXP,0,$1,$2,0,0);}
                        |   LIT_STRING restolistadeelementos  {$$ = astreeCreate(AST_LISTA_ELEM_STRING,$1,$2,0,0,0);}
;

restolistadeelementos:  ',' listadeelementos   {$$=$2;}
                        |                        {$$=0;}
                        ; 

return: KW_RETURN expressao {$$ = astreeCreate(AST_RETURN,0,$2,0,0,0);}
        ;

tipo: KW_INT  {$$ = astreeCreate(AST_KW_INT,0,0,0,0,0);}
    | KW_BOOL {$$ = astreeCreate(AST_KW_BOOL,0,0,0,0,0);}
    | KW_REAL {$$ = astreeCreate(AST_KW_REAL,0,0,0,0,0);}
    | KW_CHAR {$$ = astreeCreate(AST_KW_CHAR,0,0,0,0,0);}
    ;

literal: LIT_INT  {$$ = astreeCreate(AST_LIT_INT,$1,0,0,0,0);}
       | LIT_REAL {$$ = astreeCreate(AST_LIT_REAL,$1,0,0,0,0);}
       | LIT_TRUE {$$ = astreeCreate(AST_LIT_TRUE,$1,0,0,0,0);}
       | LIT_FALSE  {$$ = astreeCreate(AST_LIT_FALSE,$1,0,0,0,0);}
       | LIT_CHAR {$$ = astreeCreate(AST_LIT_CHAR,$1,0,0,0,0);}
       ;

%%

int yyerror(char* str)
{
    fflush(stderr);
    fprintf(stderr,"Erro na linha: %d\n", getLineNumber());
    exit(3);
}
