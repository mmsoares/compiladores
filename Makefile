etapa1: lex.yy.o hash.o y.tab.c
	gcc lex.yy.o hash.o y.tab.c -o etapa1

y.tab.c: parser.y
	yacc -d parser.y
	
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
	
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

hash.o: hash.c
	gcc -c hash.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o
	rm -rf lex.yy.*
	rm -rf y.tab.*
	rm ./etapa1
