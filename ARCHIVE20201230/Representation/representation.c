#include "representation.h"

// Table de représentation 
int representation[TAILLE_REPRESENTATION];
// Table de représentation auxilliaire (Stocke les indices où sont les numéros lexicographiques)
int representation_aux[TAILLE_REPRESENTATION];
// Son nombre d'éléments dedans
int rep = 0;
// Importation de la table lexicographique
extern lexeme table_lex[TAILLE_LEXICOGRAPHIQUE];
// Importation de la pile des régions
extern pile pile_region;
// Importation de la table des déclarations
extern declaration table_declaration[TAILLE_DECLARATION];

void creer_representation(){
    int i;
    for (i = 0; i < TAILLE_REPRESENTATION; i++)
        representation[i] = -1;
}

int inserer_tableau_table_representation(int index, int nombre_dimension){
    int i;
    while (i < TAILLE_REPRESENTATION - 2){
        if (representation[i] == -1){
            representation_aux[rep] = i;
            rep++;
            representation[i] = index;
            representation[++i] = nombre_dimension;
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion échouée
}

int inserer_dimensions_table_representation(int borne_inf, int borne_sup){
    int i;
    while (i < TAILLE_REPRESENTATION - 2){
        if (representation[i] == -1){
            representation[i] = borne_inf;
            representation[++i] = borne_sup;
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion échouée
}
int inserer_table_representation(int index, int nombre_dimension, int borne_inf, int borne_sup){
    int i = 0;
    while (i < TAILLE_REPRESENTATION - 4){ // Tant que on a de la place (Si il reste moins de 4 places alors on ne pourra pas tout insérer)
        if (representation[i] == -1){ // Si espace vide, on insère
            representation_aux[rep] = i;
            rep++;

            representation[i] = index;
            representation[i+1] = nombre_dimension;
            representation[i+2] = borne_inf;
            representation[i+3] = borne_sup;
            return 1; // L'insertion s'est bien déroulée on retourne 1
        }
    }
    return 0; // Normalement pas atteint si l'insertion a pu se dérouler
}

int inserer_structure_table_representation(int nb_champs){
    int i = 0;
    while (i < TAILLE_REPRESENTATION){ // On cherche à insérer le nombre de champs
        if (representation[i] == -1){
            representation[i] = nb_champs;
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion ratée
}

int insertion_champ_table_rep(int num_lexico, int type, int deplacement){
    int i;
    while (i < TAILLE_REPRESENTATION - 3){ // Pour faire rentrer chaque champs
        if (representation[i] == -1){
            representation[i] = type;
            representation[++i] = num_lexico;
            representation[++i] = deplacement;
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion impossible
}


int inserer_fonction_procedure_rep(int type_res, int nb_param){
    int i;
    if (type_res == -1){
        while (i < TAILLE_REPRESENTATION){ // Pour faire rentrer chaque champs
        if (representation[i] == -1){
            representation[i] = nb_param;
            representation_aux[rep] = i;
            rep++;
            return 1; // Insertion réussie
        }
        i++;
        }
    }
    while (i < TAILLE_REPRESENTATION - 2){ // Pour faire rentrer chaque champs
        if (representation[i] == -1){
            representation_aux[rep] = i;
            rep++;
            representation[i] = type_res;
            representation[++i] = nb_param;
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion impossible
}
int inserer_param_fct_proc_rep(int num_lex, int type){
    int i;
    while (i < TAILLE_REPRESENTATION - 2){ // Pour faire rentrer chaque champs
        if (representation[i] == -1){
            representation[i] = num_lex;
            representation[++i] = type;
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion impossible
}


void afficher_table_rep(){
    int nb_rep=0;
    printf("Table de représentations des sous programme\n");
    for (int i = 0; i < TAILLE_REPRESENTATION; i++){
        if (representation[i] != -1){
            printf("%d ", representation[i]);
            nb_rep++;
        }
    }
    printf("\n");
    printf("Nb rep %d\n", nb_rep);
}
