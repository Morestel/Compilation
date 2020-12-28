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
// Calcul la taille du champs execution
int remplir_exec(int numero, int nature);
// Rempli l'execution dans le cas où nature = 1 ou 2
int tailleExecution(int numero);
// Renvoie le champ execution à l'indice x
int taille(int x);
// Calcul le déplacement à l'execution depuis numero
int deplacement_execution(int numero);
// Calcul la taille du champs description
int remplir_description(int numero, int nature);
// Calcul la taille du champs region
int remplir_region(int numero, int nature);
// Ajout d'une déclaration dans la tab
void ajoutDeclaration(int newNature, int newRegion, int newDescription, int newExecution, int n);
// Ajout d'un débordement
void ajoutDebordement(int newNature, int newRegion, int newDescription, int newExecution);
// Ajout dans la table des déclarations quand on a que le numéro et la nature
void remplir_declaration(int numero, int pNature);
// Affichage table déclaration
void afficheDeclaration();
#endif