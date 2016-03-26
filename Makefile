etapa1: lex.yy.o hash.o
	gcc lex.yy.o hash.o -o etapa1

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

hash.o: hash.c
	gcc -c hash.c

main.o: main.c
	gcc -c main.c

clean:
	rm etapa1 lex.yy.c lex.yy.h *.o
