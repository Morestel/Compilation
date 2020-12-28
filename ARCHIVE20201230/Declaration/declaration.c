#include "declaration.h"

extern int *representation;
declaration table_declaration[TAILLE_DECLARATION];
int debordement = TAILLE_LEXICOGRAPHIQUE; // On utilise une variable globale pour savoir où on est dans la zone de débordement
                                          // Elle commence là où la table lexicographique s'arrête
int base_courante;
extern pile pile_region;

void init_declaration(){
    int i;
    for (i = 4; i < TAILLE_DECLARATION; i++){
        table_declaration[i].nature = -1;
        table_declaration[i].suivant = -1;
        table_declaration[i].region = -1;
        table_declaration[i].description = -1;
        table_declaration[i].execution = -1;
    }
}

// Compte le nombre de déclaration
int nombre_declaration(){
    int i;
    int nombre = 0;
    for (i = 0; i < TAILLE_DECLARATION; i++){
        if (table_declaration[i].nature != -1)
            nombre++;
    }
    return nombre;
}

// Calcul la taille du champs execution
int remplir_exec(int numero, int nature){
    int i;
    int execution = 0;
    if (i == 1 || i == 2){ 

    }
    switch(nature){
        case 1: // Type Simple
            execution = tailleExecution(numero);
            break;

        case 2: // Type Tableau
            execution = tailleExecution(numero);
            break;

        case 3: // Variable
            execution = deplacement_execution(numero);
            break;

        case 4: // Paramètre
            execution = deplacement_execution(numero);
            break;

        case 5: // Procedure
            execution = numeroRegion(); // Fonction dans Region.c
            break;

        case 6: // Fonction
            execution = numeroRegion(); // Fonction dans Region.c
            break;

        default:
            execution = 0; // Par défaut on mettra 0
            break;
    }
    return execution;
}

// Calcul la taille du champs region
int remplir_description(int numero, int nature){
    //TODO
    return 1;
}

// Calcul la taille du champs region
int remplir_region(int numero, int nature){
    //TODO
    return 1;
}

// Calcul de la taille de l'execution
int tailleExecution(int numero){
    // index dans la table contenant la description du type 
    // (table de représentation des types et des entêtes de sous-programmes)
    int index = trouver_index(numero);
    return index;
}

// Déplacement à l'execution depuis x
int deplacement_execution(int x){
    // Déplacement de 1 (indice région supérieure) + Profondeur actuelle (Avec la BC) + Exec de la région
    int deplacement;
    deplacement = 1 + base_courante + table_declaration[x].execution;
    base_courante++;
    return deplacement;
}

// Renvoie le contenu du champ execution à l'indice x
int taille(int x){
    return table_declaration[x].execution;
}

// Insère une déclaration à l'indice n 
void ajoutDeclaration(int newNature, int newRegion, int newDescription, int newExecution, int n){
    table_declaration[n].nature = newNature;
    table_declaration[n].suivant = -1; // Le suivant n'étant pas encore déterminé
    table_declaration[n].region = newRegion;
    table_declaration[n].description = newDescription;
    table_declaration[n].execution = newExecution;
}

void ajoutDebordement(int newNature, int newRegion, int newDescription, int newExecution){
    if (debordement < TAILLE_DECLARATION){ // On peut déborder
        table_declaration[debordement].nature = newNature;
        table_declaration[debordement].suivant = -1;
        table_declaration[debordement].region = newRegion;
        table_declaration[debordement].description = newDescription;
        table_declaration[debordement].execution = newExecution;
        debordement++;
    }
    else
        printf("Débordement impossible: Table remplie\n");
}

// Insère la déclaration à l'indice numero
void remplir_declaration(int numero, int pNature){
    int n = nombre_declaration();
    if (n >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        if (table_declaration[numero].nature == -1){ // Rien à cet endroit, on l'insère ici
            table_declaration[numero].nature = pNature;
            table_declaration[numero].suivant = -1;
            table_declaration[numero].region = remplir_region(numero, pNature);
            table_declaration[numero].description = remplir_region(numero, pNature);
            table_declaration[numero].execution = remplir_exec(numero, pNature);
        }
        // TODO - Gérer Débordement
    }
    
}

void afficheDeclaration(){
    int i;
    int nombre = nombre_declaration();
    printf("\n\tTable des déclarations\n");
    printf("Nature\t| Suivant\t| Région\t| Description\t| Execution\n");
    for (i = 0; i < nombre; i++){
        printf("%d\t| %d\t| %d\t| %d\t| %d\n", table_declaration[i].nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution);
    }
}

/*
int main(){
    init_declaration();
    afficheDeclaration();
    printf("%d\n", TAILLE_DECLARATION);
    exit(EXIT_SUCCESS);
}*/