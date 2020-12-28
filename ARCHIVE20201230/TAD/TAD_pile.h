#ifndef _TAD_PILE_H_
#define _TAD_PILE_H_

/* 
    TAD Pile de L2
*/

#include "liste.h"

typedef liste pile;

// Initialisation d'une pile
pile pile_vide();

// Regarde si une pile est vide
int est_pile_vide(pile p);

// Empile e sur p
pile empiler(pile p, element e);

// Renvoie premier élément de la liste
element sommet_pile(pile p);

// Depile le premier élément de la liste
pile depiler(pile p);

// Renvoie le nombre d'éléments dans la pile
int taille_pile(pile p);

#endif