#ifndef DECLARATION_H
#define DECLARATION_H

/*
    Fait le 15 Novembre 2020
    Dernière MaJ: 20 Novembre 2020
    Auteur: MORESTEL Thomas
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../TAD/TAD_pile.h"
#include "../Lexico/lexico.h"
#include "../Representation/representation.h"
#include "../Region/region.h"

typedef struct{
    int nature;
    int suivant;
    int region;
    int description;
    int execution;
}declaration;

/* Pour le champ nature */
#define TYPE_S 1
#define TYPE_T 2
#define VAR 3
#define PARAM 4
#define PROC 5
#define FCT 6

/* Taille du tableau des déclarations */
#define TAILLE_DEBORDEMENT TAILLE_LEXICOGRAPHIQUE
#define TAILLE_DECLARATION TAILLE_DEBORDEMENT + TAILLE_LEXICOGRAPHIQUE

/* Fonctions */
// Initialise la table des déclarations 
void init_declaration();

// Renvoie le champ execution à l'indice x
int taille(int x);
// Fonctions d'insertions dans la table des déclarations, leur nom indique ce qu'on insère
int declaration_structure(int numero, int type, int numero_region, int indice_representation);
int declaration_tableau(int numero, int type, int nombre_dimensions, int numero_region, int indice_representation);
int declaration_variable(int numero, int type, int deplacement, int numero_region);
int declaration_parametre(int numero, int type, int deplacement, int numero_region);
int declaration_procedure(int numero, int type, int numero_region, int indice_representation);
int declaration_fonction(int numero, int type, int numero_region, int indice_representation);

int gerer_debordement(int numero);
// Affichage table déclaration
void afficheDeclaration();
void afficheDebordement();
#endif