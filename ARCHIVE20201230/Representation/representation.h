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


// Fonctions d'insertion dans la table de représentation

int inserer_structure_table_representation(int nb_champs);
int update_structure_rep(int nb_champs);
int insertion_champ_table_rep(int num_lexico, int type, int deplacement);

int inserer_tableau_table_representation(int type, int nombre_dimension);
int laisser_espace_tab(int espace);
int inserer_dimensions_table_representation(int borne_inf, int borne_sup);

int inserer_fonction_procedure_rep(int type_res, int nb_param);
int inserer_param_fct_proc_rep(int num_lex, int type);

void afficher_table_rep();


#endif