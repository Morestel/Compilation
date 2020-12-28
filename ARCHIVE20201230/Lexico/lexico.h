#ifndef LEXICO_H
#define LEXICO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TAILLE_LEXICOGRAPHIQUE 500

typedef struct{
    int taille; // Taille du lexème
    char contenu[100]; // Son contenu
    int suivant; // Le suivant
}lexeme;

int hashcode(char *lexeme); // Défini le hashcode pour ce lexème

void initialise(); // Initialisation des deux tableaux

int inserer_lexicographique(char *elem); // Stockage de l'élément dans la table des lexèmes

int num_lexicographique(char *s); // Renvoie le numéro lexicographique du lexème s

void afficheLexico(); // Affichage table lexème

void afficheHashcode(); // Affichage table hashcode

// Pour un lexeme donné, renvoie le numéro de déclaration
int association_nom(char *lexeme);

// Renvoie valeur en chaine de caractère
char* itos(int valeur);

void initialise_lex(lexeme table[], int hash[]); // Initialisation de la table de hashage à -1 & des 4 premières cases de table_lex
void insertion(lexeme table[], int hashtable[], char *elem); // Stockage de l'élément dans la table des lexèmes
void afficheLexicoTable(lexeme table[]);

#endif

