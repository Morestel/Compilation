YACC = yacc
LEX = lex
CC = gcc
CC2 = y.tab.c lex.yy.o -ly -lfl

all: y.tab.c lex.yy.o
	$(CC) -o wati $(CC2)
lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c
y.tab.c: cpyrr.y
	$(YACC) -d -v cpyrr.y
lex.yy.c: cpyrr.l y.tab.h
	$(LEX) cpyrr.l

propre:
	rm *.o y.tab.* y.output lex.yy.c