#ifndef _LISTE_H
#define _LIS

/* 
    TAD liste de L2
*/

#include <stdio.h>
#include "allocation.h"

typedef int element;

typedef struct cellule{
    element objet;
    struct cellule * suivant;
}struct_cellule;

typedef struct_cellule * liste;

/* Renvoie liste vide */
liste liste_vide();

/* Test si une liste est vide */
int est_liste_vide(liste l);

/* Ajout d'un element eleme à la liste l */
liste inserer_element_liste(liste l, element elem);

/* Renvoie le premier element de la liste l */
element renvoie_premier_liste(liste l);

/* Supprime la première cellule de la liste l */
liste supprimer_premier_liste(liste l);

#endif