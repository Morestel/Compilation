#ifndef ARBRE_H
#define ARBRE_H
/* 
    Fait le 14 Novembre 2020
    Auteur: MORESTEL Thomas
*/

// Arbre abstrait

#include <stdlib.h>
#include <stdio.h>

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
