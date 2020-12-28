#ifndef REPRESENTATION_H
#define REPRESENTATION_H

/* 
    Fait le 15 Novembre
    Auteur: MORESTEL Thomas
    Dernière modification: 18 Décembre 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Lexico/lexico.h"
#include "../Region/region.h"
#include "../Declaration/declaration.h"

#define TAILLE_REPRESENTATION 200

// Création de la table de representation
void creer_representation();
// Insertion dans la table de représentation avec un indice en paramètre
void inserer_representation_indice(int i, int x);
// Insertion dans la table de représentation sans indice en paramètre
int inserer_representation(int x);
// Donne l'index de la valeur x
int trouver_index(int x);

// Fonction d'insertion 
int inserer_table_representation(int index, int nombre_dimension, int borne_inf, int borne_sup);
int inserer_fonction_procedure_table_representation(int resultat, int nb_param, char *num_lexico, int *type);
int stockage_table_rep(int un, int deux, int deplacement);

int inserer_structure_table_representation(int nb_champs);
int insertion_champ_table_rep(int num_lexico, int type, int deplacement);

int inserer_tableau_table_representation(int index, int nombre_dimension);
int inserer_dimensions_table_representation(int borne_inf, int borne_sup);

int inserer_fonction_procedure_rep(int type_res, int nb_param);
int inserer_param_fct_proc_rep(int num_lex, int type);

void afficher_table_rep();
void afficher_representation(int *tab);

#endif