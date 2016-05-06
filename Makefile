etapa4: clean y.tab.o lex.yy.o main.o astree.o hash.o semantic.o
	gcc -o etapa4 y.tab.o lex.yy.o main.o astree.o hash.o semantic.o -w
main.o: main.c lex.yy.c
	gcc -c main.c -w
astree.o: astree.c
	gcc -c astree.c -w
hash.o: hash.c
	gcc -c hash.c -w
semantic.o: semantic.c
	gcc -c semantic.c -w
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -w
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
y.tab.o: y.tab.c
	gcc -c y.tab.c -w
y.tab.c: y.tab.h
	yacc parser.y
y.tab.h: parser.y
	yacc -d -v parser.y
clean:
	rm -rf *.o lex.yy.* y.tab.* y.output etapa4 *~
