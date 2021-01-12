YACC = yacc
LEX = lex
CC = gcc -g
CC2 = y.tab.c lex.yy.o 
LDFLAGS = -ly -lfl
OPTIONS = -Wall

all: y.tab.c lex.yy.o
	$(CC) -o wati $(CC2) Lexico/lexico.c Lexico/lexico.h Representation/representation.c Representation/representation.h Declaration/declaration.c Declaration/declaration.h Region/region.c Region/region.h TAD/TAD_pile.h TAD/TAD_pile.c TAD/arbre.h TAD/arbre.c TAD/liste.c TAD/liste.h TAD/allocation.c TAD/allocation.h $(LDFLAGS)
lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c
y.tab.c: cpyrr.y
	$(YACC) -d -v cpyrr.y
lex.yy.c: cpyrr.l y.tab.h
	$(LEX) cpyrr.l


lexico.o: Lexico/lexico.c Lexico/lexico.h
	$(CC) $(OPTIONS) Lexico/lexico.c Lexico/lexico.h -o $@

region.o: Region/region.c Region/region.h TAD/TAD_pile.h TAD/TAD_pile.c TAD/arbre.h TAD/arbre.c TAD/liste.c TAD/liste.h TAD/allocation.c TAD/allocation.h
	$(CC) $(OPTIONS) $^ -o $@

representation.o: Representation/representation.c Representation/representation.h Lexico/lexico.h Lexico/lexico.c Declaration/declaration.c Declaration/declaration.h Region/region.c Region/region.h TAD/TAD_pile.h TAD/TAD_pile.c TAD/arbre.h TAD/arbre.c TAD/liste.c TAD/liste.h TAD/allocation.c TAD/allocation.h
	$(CC) $(OPTIONS) $^ -o $@

declaration.o: Representation/representation.c Representation/representation.h Lexico/lexico.h Lexico/lexico.c Declaration/declaration.c Declaration/declaration.h Region/region.c Region/region.h TAD/TAD_pile.h TAD/TAD_pile.c TAD/arbre.h TAD/arbre.c TAD/liste.c TAD/liste.h TAD/allocation.c TAD/allocation.h
	$(CC) $(OPTIONS) $^ -o $@
	
propre:
	rm *.o y.tab.* y.output lex.yy.c wati