#ifndef REGION_H
#define REGION_H

/*
    Fait le 14 Novembre
    Auteur: MORESTEL Thomas
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "../TAD/arbre.h"
#include "../TAD/TAD_pile.h"

#define TAILLE_REGION 20

typedef struct{
    int taille; // Taille
    int nis; // Niveau d'imbrication de la région
    arbre arbre_r; // Arbre de la région
}region;

// Initialise la table des régions
void init_region();
// Donne le nombre de région du tableau
int nombre_region();
// Ajout d'une région dans le tableau
void ajoutRegion(int newTaille, int newNis, arbre newArbre);
// Insertion juste d'un arbre à l'indice i
void ajout_arbre_region(int i, arbre newArbre);
// Affiche la table des regions
void affiche_region();
#endif