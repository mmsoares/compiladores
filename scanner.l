%{
int running = 1;
int lineNumber = 1;
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

char *removeQuotes(char *string);
void initMe(void);
%}

%x COMM

%%
[ \t]+ {}    //espaço em branco ou tabulação
"\n" lineNumber++;  //incremento do contador de linhas

int return KW_INT;
real return KW_REAL;
bool return KW_BOOL;
char return KW_CHAR;
if return KW_IF;
else return KW_ELSE;
while return KW_WHILE;
input return KW_INPUT;
output return KW_OUTPUT;
return return KW_RETURN;

","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$" return yytext[0];  //caracteres especiais

"<=" return OPERATOR_LE;
">=" return OPERATOR_GE;
"==" return OPERATOR_EQ;
"!=" return OPERATOR_NE;
"&&" return OPERATOR_AND;
"||" return OPERATOR_OR;

\'.\' {
  //caractere
  char stringHelper[strlen(yytext)];
  strcpy(stringHelper, yytext);   //usada para não modificar o valor de yytext pois isso pode gerar erros na leitura dos próximos simbolos
  char* unquotedString = removeQuotes(stringHelper);       //remove as aspas no começo e no fim do caracter

  yylval.symbol = hashInsert(unquotedString, SYMBOL_LIT_CHAR);   //insere na tabela de simbolos
  return SYMBOL_LIT_CHAR;
}

\"([^\"])*\" {
  //string
  char stringHelper[strlen(yytext)];
  strcpy(stringHelper, yytext);  //usada para não modificar o valor de yytext pois isso pode gerar erros na leitura dos próximos simbolos
  char* unquotedString = removeQuotes(stringHelper);     //remove as aspas no começo e no fim da string

  yylval.symbol = hashInsert(unquotedString, SYMBOL_LIT_STRING);  //insere na tabela de simbolos
  return SYMBOL_LIT_STRING;
}

[0-9]+ {
  //inteiro
  yylval.symbol = hashInsert(yytext, SYMBOL_LIT_INT);   //insere na tabela de simbolos
  return SYMBOL_LIT_INT;
}

FALSE {
  yylval.symbol = hashInsert(yytext, SYMBOL_LIT_TRUE);
  return SYMBOL_LIT_FALSE;
}

TRUE {
  yylval.symbol = hashInsert(yytext, SYMBOL_LIT_FALSE);
  return SYMBOL_LIT_TRUE;
}

[A-Za-z]([A-Za-z]|[0-9]|"_")* {
  //identificador
  yylval.symbol = hashInsert(yytext, SYMBOL_IDENTIFIER);   //insere na tabela de simbolos
  return SYMBOL_IDENTIFIER;
}

\/\/(.)+ {}    //comentarios de linha unica no formato barra barra

"/*"			{ BEGIN(COMM); }   //comentarios com multiplas linhas no formato barra asterisco (texto ...) asterisco barra
<COMM>"*/"    { BEGIN(INITIAL); }
<COMM>"\n"    { ++lineNumber;  }
<COMM>.       { }

.		 { return TOKEN_ERROR; }

%%
//rotina que remove o primeiro e o último caracter de uma string - usada para remover as aspas de strings e caracteres
char *removeQuotes(char *string){
  char *p = string;
  p++; //incrementa o ponteiro para remover o primeiro caracter
  p[strlen(p)-1] = '\0';   //muda o valor do ultimo caracter pra \0, que é indicativo de final de palavra, assim efetivamente removendo o último caracter

  return p;
}

int isRunning(void){
 return running;
}

int yywrap(void) {
 running = 0;
 return 1;
}

int getLineNumber(void){
 return lineNumber;
}

void initMe(void){
  hashInit();
}

#include "main.c"
