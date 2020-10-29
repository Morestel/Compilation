%{
#include "y.tab.h"
int num_ligne = 1;
%}

%%

wati_programme {return (PROG);}
wati_debut {return (WATI_DEBUT);}
wati_fin {return (WATI_FIN);}

\+ {return (PLUS);}
\- {return (MOINS);}
\* {return (MULT);}
\/ {return (DIV);}
\%	{return(MOD);}

\( {return (PARENTHESE_OUVRANTE);}
\) {return (PARENTHESE_FERMANTE);}
\{	{return(ACCOLADE_OUVRANTE);}
\}	{return(ACCOLADE_FERMANTE);}
[[] {return(CROCHET_OUVRANT);}
[]] {return(CROCHET_FERMANT);}

\:	{return(DEUX_POINTS);}
\,	{return(VIRGULE);}
\;	{return(POINT_VIRGULE);}


==	{return(EGAL);}
\<	{return(INFERIEUR);}
>	{return(SUPERIEUR);}
\<= {return(INFERIEUR_EGAL);}
>=	{return(SUPERIEUR_EGAL);}
!=	{return(DIFFERENT);}
!	{return(NOT);}
= {return(AFFECTE);}
\&\& {return(ET);}
\|\| {return(OU);}
\+\+ {return(INC);}
\-\- {return(DEC);}
\+= {return(OP_AFPL);}
\-= {return(OP_AFMO);}

if {return(SI);}
else {return(SINON);}
while {return(TANT_QUE);}
do {return(FAIRE);}
for {return(POUR);}
switch {return(SWITCH);}
case {return(CASE);}
default {return(DEFAULT);}

0|[1-9][0-9]* {return(CST_ENTIERE);}
0|[1-9][0-9]*\.[0-9]+ {return(CST_REEL);}
\'[a-zA-Z]\' {return(CST_CARACTERE);}
\"[^\"\n]+\" {return(CST_CHAINE);}

let {return(VARIABLE);}
int {return(ENTIER);}
char {return(CARACTERE);}
string {return(CHAINE);}
bool {return(BOOLEEN);}
float {return(REEL);}
tab {return(TABLEAU);}
typedef {return(TYPE);}
struct {return(STRUCT);}
of {return(DE);}

true {return(TRUE);}
false	 {return(FALSE);}

fct {return(FONCTION);}
return {return(RETOURNE);}
procedure {return(PROCEDURE);}

\/\*([^*]|\*+[^*/])*\*+\/ {;}	/* Commentaire multilignes */
\/\/.* {;}	/* Commentaire sur une seule ligne */
[\n] {num_ligne++;}
[ \t] {;} 
[a-zA-Z][a-zA-Z0-9_]* {return(IDF);}

%%