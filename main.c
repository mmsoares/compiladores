int main(){
 
 int tok;

 hashInit();
 printf("Hash initialized\n");

 while(isRunning()){
  tok = yylex();
  printf("LINE: [%d] - TEXT: [%s] - TOKEN: [%d]\n", getLineNumber(), yytext, tok);
 }
 printf("going to print the hash\n");
 hashPrint();
}
