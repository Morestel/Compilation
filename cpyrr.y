%{
    extern char* yytext;
#include <stdio.h>
#include <stdlib.h>
    extern int num_ligne;
    int yyerror(){
        printf("Erreur de syntaxe en ligne %d\n", num_ligne);
    }
    int yylex();
    %}

%token PROG
%token WATI_DEBUT WATI_FIN
%token PLUS MOINS MULT DIV MOD
%token PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE ACCOLADE_FERMANTE
%token CROCHET_OUVRANT CROCHET_FERMANT
%token POINT_VIRGULE DEUX_POINTS POINT VIRGULE
%token OU ET DIFFERENT NOT AFFECTE EGAL SUPERIEUR INFERIEUR 
%token INC DEC
%token SUPERIEUR_EGAL INFERIEUR_EGAL
%token OP_AFPL OP_AFMO
%token SI SINON
%token SWITCH DEFAULT CASE
%token TANT_QUE FAIRE POUR

%token CST_ENTIERE CST_REEL CST_CARACTERE CST_CHAINE
%token TYPE IDF VARIABLE ENTIER REEL BOOLEEN CARACTERE CHAINE
%token TRUE FALSE
%token STRUCT
%token TABLEAU DE

%token PROCEDURE FONCTION RETOURNE

%token VIDE

%%

programme: PROG corps
;

corps: liste_declarations liste_instructions
     | liste_instructions
;

liste_declarations: declaration POINT_VIRGULE
                  | liste_declarations declaration POINT_VIRGULE
;

liste_instructions: ACCOLADE_OUVRANTE suite_liste_inst ACCOLADE_FERMANTE
;

suite_liste_inst: instruction
                | suite_liste_inst instruction
;

declaration: declaration_type
           | declaration_variable
           | declaration_procedure
           | declaration_fonction
;

/*           Structure  
               && 
             Tableaux 
*/
declaration_type: TYPE STRUCT IDF suite_declaration_type
;

suite_declaration_type: ACCOLADE_OUVRANTE liste_champs ACCOLADE_FERMANTE
                      | TABLEAU dimension DE nom_type
;

dimension: CROCHET_OUVRANT CST_ENTIERE CROCHET_FERMANT
         | CROCHET_OUVRANT CST_ENTIERE CROCHET_FERMANT dimension
;

liste_champs: un_champ
            | liste_champs POINT_VIRGULE un_champ
;

un_champ: IDF DEUX_POINTS nom_type
;

nom_type: type_simple
        | IDF
;

/* Type de base */
type_simple: ENTIER
           | REEL
           | BOOLEEN
           | CARACTERE
           | CHAINE CROCHET_OUVRANT CST_ENTIERE CROCHET_FERMANT
;

/* Declaration */
declaration_variable: VARIABLE IDF DEUX_POINTS nom_type
;

declaration_procedure: PROCEDURE IDF liste_parametres corps
;

declaration_fonction: FONCTION IDF liste_parametres RETOURNE type_simple corps
;

liste_parametres: PARENTHESE_OUVRANTE PARENTHESE_FERMANTE 
                | PARENTHESE_OUVRANTE liste_param PARENTHESE_FERMANTE 
;

liste_param: un_param
           | un_param VIRGULE liste_param
;

un_param: type_simple IDF
;
/* Instructions de base*/
instruction: affectation POINT_VIRGULE
           | condition
           | switch
           | tant_que
           | faire_tant_que
           | pour
           | appel
           | VIDE
           | RETOURNE resultat_retourne POINT_VIRGULE
           | POINT_VIRGULE
;

/* Return : Possible de juste écrire "return" */
resultat_retourne:
                 | expression
;

/* Appel des fonctions */
appel: IDF liste_arguments
;

liste_arguments: PARENTHESE_OUVRANTE PARENTHESE_FERMANTE
               | PARENTHESE_OUVRANTE liste_args PARENTHESE_FERMANTE
;

liste_args: un_arg
          | liste_args VIRGULE un_arg
;

un_arg: expression
;

/* If / Else / Switch */
condition: SI PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE liste_instructions SINON liste_instructions
         | SI PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE liste_instructions SINON condition
         | SI PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE condition
         | SI PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE liste_instructions
;

switch: SWITCH expression ACCOLADE_OUVRANTE switch_core default ACCOLADE_FERMANTE
;

switch_core: switch_core CASE expression DEUX_POINTS suite_liste_inst
            | CASE expression DEUX_POINTS suite_liste_inst
;

default: DEFAULT DEUX_POINTS suite_liste_inst
       |
;

/* Boucle while / Do while*/
tant_que: TANT_QUE PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE liste_instructions
;

faire_tant_que: FAIRE liste_instructions TANT_QUE PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE POINT_VIRGULE
;

/* Boucle for */
pour: POUR PARENTHESE_OUVRANTE affecta_pour POINT_VIRGULE compa_pour POINT_VIRGULE affecta_pour PARENTHESE_FERMANTE liste_instructions
;

affecta_pour: affectation
            |
;

compa_pour: comparaison
           | 
;

/* Affectation */
affectation: variable AFFECTE expression
           | variable OP_AFMO expression
           | variable OP_AFPL expression
           | variable INC
           | variable DEC
;

/* Définition de variable */
variable: IDF
;

/* Expression: +, -,*, /, , %, &&, ||, !, vrai, faux
   Mais aussi des comparaisons & appels de fonctions (Pour pouvoir faire x = truc())
*/

expression: expression PLUS expression2
          | expression MOINS expression2
          | expression OU expression2
          | comparaison
          | expression2
;

expression2: expression2 MULT expression3
           | expression2 DIV expression3
           | expression2 MOD expression3
           | expression2 ET expression3
           | expression3
;

expression3: variable
           | appel
           | NOT expression3
           | CST_ENTIERE
           | CST_REEL
           | CST_CARACTERE
           | CST_CHAINE
           | TRUE
           | FALSE
           | PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE
;

/* Compare deux expressions */
comparaison: expression comparateur expression2
;

/* Liste des comparateurs */
comparateur: EGAL
           | INFERIEUR 
           | SUPERIEUR
           | INFERIEUR_EGAL
           | SUPERIEUR_EGAL
           | DIFFERENT
;

%%
