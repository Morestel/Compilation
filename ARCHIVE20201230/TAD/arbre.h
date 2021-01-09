#ifndef ARBRE_H
#define ARBRE_H
/* 
    Fait le 14 Novembre 2020
    Auteur: MORESTEL Thomas
*/

// Arbre abstrait

#include <stdlib.h>
#include <stdio.h>


/* Type simple */
#define AA_TB_INT 0
#define AA_TB_FLOAT 1
#define AA_TB_BOOL 2
#define AA_TB_CHAR 3
#define AA_TB_STRING 4

/* Operateur */
#define AA_PLUS 33
#define AA_MOINS 34
#define AA_MULT 35
#define AA_DIV 36
#define AA_MOD 37

/* Comparateur */
#define AA_SUPP 5
#define AA_INF 6
#define AA_EGAL 7
#define AA_DIFF 8
#define AA_SUPP_EG 9
#define AA_INF_EG 10

/* Opérateur Booléen */
#define AA_ET 11
#define AA_OU 12

/* Conditionnel */
#define AA_SI 13
#define AA_ALORS 14
#define AA_TANT_QUE 15

/* Controlleur */
#define AA_APPEL_PROC 16
#define AA_RETURN 20
#define AA_APPEL_FCT 21


/* Affectation */
#define AA_AFFECT 22

/* Constante */
#define AA_CSTE_INT 23
#define AA_CSTE_FLOAT 24
#define AA_CSTE_BOOL 25
#define AA_CSTE_CHAR 26
#define AA_CSTE_STRING 27

/* Fonction Predefini */
#define AA_WRITE 28
#define AA_READ 29

/* Vide */
#define AA_VIDE 30

/* IDF */
#define AA_IDF 31

/* Tableau */
#define AA_TAB 32
#define AA_P 38

/*Liste */
#define AA_LISTE 39


typedef struct noeud{
    int nature; // Nature du noeud
    int nlex; // Son numéro lexical
    int ndecl; // Son numéro de déclaration
    struct noeud *frere; // Noeud frère
    struct noeud *fils; // Noeud fils
}noeud;

typedef struct noeud * arbre;

/* Fonctions */
// Création de noeud
arbre creer_noeud(int nature, int lexical, int decla);
// Savoir si un noeud est une feuille
int est_feuille(arbre a);
// Concaténation père frère
arbre concat_pere_frere(arbre pPere, arbre pFrere);
// Concaténation père fils
arbre concat_pere_fils(arbre pPere, arbre pFils);

#endif
