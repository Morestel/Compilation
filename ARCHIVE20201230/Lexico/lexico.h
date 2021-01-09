#ifndef LEXICO_H
#define LEXICO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TAILLE_LEXICOGRAPHIQUE 500
#define TAILLE_HASHCODE 31

typedef struct{
    int taille; // Taille du lexème
    char contenu[100]; // Son contenu
    int suivant; // Le suivant
}lexeme;

int hashcode(char *lexeme); // Défini le hashcode pour ce lexème

void initialise(); // Initialisation des deux tableaux

int inserer_lexicographique(char *elem); // Stockage de l'élément dans la table des lexèmes

void afficheLexico(); // Affichage table lexème

void afficheHashcode(); // Affichage table hashcode

// Pour un lexeme donné, renvoie le numéro de déclaration
int association_nom(char *lexeme);


#endif