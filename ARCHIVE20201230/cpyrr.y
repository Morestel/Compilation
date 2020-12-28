%{
    extern char* yytext;
#include <stdio.h>
#include <stdlib.h>
#include "couleur.h"
#include "Declaration/declaration.h"
#include "Lexico/lexico.h"
//#define YYSTYPE char *

    extern int num_ligne;
    int yyerror(){
        couleur(JAUNE);
        printf("L.%d: ", num_ligne);
        couleur(ROUGE);
        printf("Erreur: ");
        couleur(REINIT);
        printf("Syntaxe incorrecte\n");
    }
    int yylex();
    int nombre_parametre = 0;
    int num_region;
    int NIS;
    int deplacement;
    extern lexeme table_lex[TAILLE_LEXICOGRAPHIQUE];
    extern int hashtab[TAILLE_LEXICOGRAPHIQUE];
    extern int representation[TAILLE_REPRESENTATION];
    %}

%token PROG
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
%token LIRE ECRIRE

%union {
    struct noeud* arbre;
    int entier;
    }

//%type <entier> ENTIER REEL BOOLEEN CARACTERE CHAINE
%type <entier> CST_ENTIERE CST_CARACTERE CST_REEL CST_CHAINE IDF
%type <entier> type_simple nom_type
%type <entier> variable
%type <entier> un_champ liste_champs
%type <entier> dimension
%type <entier> un_param
//%type <entier> declaration_variable declaration_type
//%type <entier> declaration_fonction
%start programme
%%

programme: PROG {initialise(); creer_representation();} corps
;

corps: {num_region = 0; NIS = 0; deplacement = 0;} liste_declarations liste_instructions
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
declaration_type: TYPE STRUCT IDF {deplacement = 0;} suite_declaration_type
;

suite_declaration_type: ACCOLADE_OUVRANTE liste_champs ACCOLADE_FERMANTE {inserer_structure_table_representation($2);}  
                      | TABLEAU dimension DE nom_type {inserer_tableau_table_representation($4, $2);}
; /* Normalement le nombre de champ est compté dans liste champs, on récupère juste la valeur qu'on insère dans la première case de
la structure dans la table des représentations */
/* Idem pour les tableaux dimension contient le nombre de dimensions du tableau 
*/

dimension: CROCHET_OUVRANT CST_ENTIERE CROCHET_FERMANT  {$$++; inserer_dimensions_table_representation(0, $2);}
         | CROCHET_OUVRANT CST_ENTIERE CROCHET_FERMANT dimension {$$++; inserer_dimensions_table_representation(0, $2);}
         | CROCHET_OUVRANT IDF CROCHET_FERMANT {$$++; inserer_dimensions_table_representation(0, $2);}
         | CROCHET_OUVRANT IDF CROCHET_FERMANT dimension {$$++; inserer_dimensions_table_representation(0, $2);}
;

liste_champs: un_champ {$$ += $1;}
            | liste_champs POINT_VIRGULE un_champ
;

un_champ: IDF DEUX_POINTS nom_type {insertion_champ_table_rep($1, $3, deplacement); deplacement += taille($3);}
;

nom_type: type_simple
        | IDF /*{$$ = itos(association_nom($1));}*/
;

/* Type de base */
type_simple: ENTIER {$$ = 0;}
           | REEL {$$ = 1;}
           | BOOLEEN {$$ = 2;}
           | CARACTERE {$$ = 3;}
           | CHAINE CROCHET_OUVRANT CST_ENTIERE CROCHET_FERMANT {$$ = 4;}
;

/* Declaration */
declaration_variable: VARIABLE IDF DEUX_POINTS nom_type
                    | VARIABLE IDF dimension DEUX_POINTS nom_type
;

declaration_procedure: PROCEDURE {num_region++; NIS++; deplacement = 1 + NIS; } IDF liste_parametres corps {NIS--; inserer_fonction_procedure_rep(-1, nombre_parametre);}
;

declaration_fonction: FONCTION {num_region++; NIS++; deplacement = 1 + NIS; } IDF liste_parametres RETOURNE type_simple corps {NIS--; inserer_fonction_procedure_rep($6, nombre_parametre);;}
;

liste_parametres: PARENTHESE_OUVRANTE PARENTHESE_FERMANTE 
                | PARENTHESE_OUVRANTE liste_param PARENTHESE_FERMANTE 
;

liste_param: un_param
           | un_param VIRGULE liste_param
;

un_param: type_simple IDF {nombre_parametre++; inserer_param_fct_proc_rep($2, $1);}
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
           | lecture
           | ecriture
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
        | IDF dimension // Accès à un tableau
        | IDF POINT IDF // Accès aux champs d'une structure
        | IDF POINT IDF dimension // Accès aux champs d'une structure qui est un tableau
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

/* Lecture écriture */

lecture: LIRE PARENTHESE_OUVRANTE CST_CHAINE liste_variables PARENTHESE_FERMANTE
;

liste_variables: VIRGULE variable
               | liste_variables VIRGULE variable
;

ecriture: ECRIRE PARENTHESE_OUVRANTE CST_CHAINE suite_ecriture PARENTHESE_FERMANTE
;

suite_ecriture: 
              | VIRGULE variable suite_ecriture
;

%%
int main(void){
    yyparse();
    afficheLexico();
    afficher_table_rep();
    return 0;
    //initialise(); // Initialise la tablelexicographique et la table des hascodes
    //afficheLexico();
}