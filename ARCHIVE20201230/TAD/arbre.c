/*
    Fait le 14 Novembre 2020
    Auteur: MORESTEL Thomas
*/

#include "arbre.h"

// Fonction de création de noeuds
arbre creer_noeud(int nature, int lexical, int decla){
    arbre noeud;
    noeud = (arbre) malloc(sizeof(noeud));
    noeud->nature = nature;
    noeud->nlex = lexical;
    noeud->ndecl = decla;
    return noeud;
}

// Fonction booléenne pour savoir si un noeud est une feuille
int est_feuille(arbre a){
    if (a->fils == NULL)
        return 1;
    else 
        return 0;
}

// Concaténation de l'arbre père et de l'arbre frère
arbre concat_pere_frere(arbre pPere, arbre pFrere){
    if (pFrere == NULL)
        return pPere;
    pPere->frere = pFrere;
    return pPere;
}

// Concaténation de l'arbre père et de l'arbre fils
arbre concat_pere_fils(arbre pPere, arbre pFils){
    if (pFils == NULL)
        return pPere;
    pPere->frere = pFils;
    return pPere;
}

void free_arbre(arbre a){
    if (a == NULL){
        return;
    }
    else{
        free(a->frere);
        free(a->fils);
        free(a);
    }
}