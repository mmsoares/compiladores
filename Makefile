etapa3: clean y.tab.o lex.yy.o main.o hash.o astree.o
	gcc -o etapa3 y.tab.o lex.yy.o main.o hash.o astree.o
main.o: main.c lex.yy.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
astree.o: astree.c
	gcc -c astree.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: y.tab.h
	yacc parser.y
y.tab.h: parser.y
	yacc -d -v parser.y
		
clean:
	rm -rf *.o lex.yy.* y.tab.* y.output etapa3
