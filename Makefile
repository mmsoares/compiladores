LEX     = flex
YACC    = yacc -y
YFLAGS  = -d
objects = scan.o parser.o main.o

etapa2: $(objects)

scan.o: scanner.l parser.c

parser.o: parser.y

main.o: main.c

clean:
	rm -rf *.o
	rm ./etapa2
