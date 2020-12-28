#include "representation.h"

// Table de représentation 
int representation[TAILLE_REPRESENTATION];
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

void inserer_representation_indice(int i, int x){
    representation[i] = x;
}

int inserer_representation(int x){
    int i = 0;
    for (i = 0; i < TAILLE_REPRESENTATION; i++){
        if (representation[i] == -1){
            representation[i] = x;
            return 1; // On a inséré notre valeur, on retourne 1
        }
    }
    return 0; // Insertion impossible, on retourne 0
}

int inserer_tableau_table_representation(int index, int nombre_dimension){
    int i;
    while (i < TAILLE_REPRESENTATION - 2){
        if (representation[i] == -1){
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

int inserer_fonction_procedure_table_representation(int resultat, int nb_param, char *num_lexico, int *type){
    int i = 0;
    int j;
    while (i < TAILLE_REPRESENTATION - nb_param*2){ // Tq il y a de la place pour tout
        if (representation[i] == -1){
            if (resultat == 0 || resultat == 1 || resultat == 2 || resultat == 3){ // Si c'est une fonction on insère le type du résultat
                representation[i] = resultat;
                i++; // Pour insérer nb_param juste après
            }
            representation[i] = nb_param; // Cas fonction: nb_param est à i+1, si procédure nb_param est à i
            for (j = 0; j < nb_param; j++){
                representation[++i] = num_lexicographique(num_lexico);
                representation[++i] = type[j];
            }
            return 1; // Insertion réussie
        }
        i++;
    }
    return 0; // Insertion ratée
}

int inserer_fonction_procedure_rep(int type_res, int nb_param){
    int i;
    if (type_res == -1){
        while (i < TAILLE_REPRESENTATION){ // Pour faire rentrer chaque champs
        if (representation[i] == -1){
            representation[i] = nb_param;
            return 1; // Insertion réussie
        }
        i++;
    }
    }
    while (i < TAILLE_REPRESENTATION - 2){ // Pour faire rentrer chaque champs
        if (representation[i] == -1){
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

int stockage_table_rep(int un, int deux, int deplacement){
    
}

int trouver_index(int x){
    int i;
    for (i = 0; i < TAILLE_REPRESENTATION; i++){ // Parcours de la table des représentations
        if (representation[i] == x) // Recherche correspondance entre le int à l'indice i et x
            return i; // Renvoie de l'index
    }
    // On a pas trouvé l'index
    return -1;
}

void afficher_table_rep(){
    for (int i = 0; i < TAILLE_REPRESENTATION; i++){
        printf("%d ", representation[i]);
    }
    printf("\n");
}

void afficher_representation(int *tab){
    for (int i = 0; i < TAILLE_REPRESENTATION; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}