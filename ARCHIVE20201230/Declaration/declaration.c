#include "declaration.h"

extern int representation[TAILLE_REPRESENTATION];
extern region table_reg[TAILLE_REGION];
lexeme table_lex[TAILLE_LEXICOGRAPHIQUE];
declaration table_declaration[TAILLE_DECLARATION];
int debordement = TAILLE_LEXICOGRAPHIQUE; // On utilise une variable globale pour savoir où on est dans la zone de débordement
                                          // Elle commence là où la table lexicographique s'arrête
int base_courante;
extern pile pile_region;

int nb_declaration = 0;

void init_declaration(){
    int i;
    nb_declaration = 4;
    for (i = 0; i < 4; i++){
        table_declaration[i].nature = -1;
        table_declaration[i].suivant = -1;
        table_declaration[i].region = -1;
        table_declaration[i].description = -1;
        table_declaration[i].execution = 1;  
    }
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

// Renvoie le contenu du champ execution à l'indice x
int taille(int x){
    return table_declaration[x].execution;
}

int declaration_structure(int numero, int type, int num_region, int indice_representation){
    int vDescription;
    int i;
    int indice;
    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero);
        if (indice != numero){ // Si il doit y avoir débordement 
            
                table_declaration[numero].suivant = indice;
            table_declaration[indice].nature = TYPE_S; // Correspond aux structures
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = type; 
                nb_declaration++;
                return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = TYPE_S; // Correspond aux structures
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = type; 
                nb_declaration++;
                return 1;
            }
        }
    }
    return 0;
}


int declaration_tableau(int numero, int type, int nombre_dimensions, int num_region, int indice_representation){
    int vDescription;
    int i;
    int indice;
    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero);
        if (indice != numero){ // Si il doit y avoir débordement 
            
            table_declaration[numero].suivant = indice;
            table_declaration[indice].nature = TYPE_T; // Correspond aux tableaux
            table_declaration[indice].suivant = -1;
            table_declaration[indice].region = num_region;
            table_declaration[indice].description = indice_representation;
            table_declaration[indice].execution = nombre_dimensions * type + type;
                return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = TYPE_T; // Correspond aux tableaux
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = nombre_dimensions * type + type;
                return 1;
            }  
        }
    }
    return 0;
}

int declaration_variable(int numero, int type, int deplacement, int num_region){
    int vDescription;
    int i;
    int indice;

    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero);
        if (indice != numero){ // Si il doit y avoir débordement 
            
                table_declaration[numero].suivant = indice;
                table_declaration[indice].nature = VAR; // Correspond aux variables
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = type;
                table_declaration[indice].execution = deplacement;
                return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = VAR; // Correspond aux variables
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = type;
                table_declaration[indice].execution = deplacement;
                return 1;
            }
        }
    }
    return 0;
}


int declaration_parametre(int numero, int type, int deplacement, int num_region){
    int vDescription;
    int i;
    int indice;

    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero); // Indice n'a soit pas bouger soit il contient l'endroit du prochain élément à insérer dans débordement
        if (indice != numero){ // Si il doit y avoir débordement 
            // On a désormais l'endroit où insérer: On insère
             table_declaration[numero].suivant = indice; // MAJ de la colonne suivant à l'indice numéro
             table_declaration[indice].nature = PARAM; // Correspond aux paramètres
            table_declaration[indice].suivant = -1;
            table_declaration[indice].region = num_region;
            table_declaration[indice].description = type;
            table_declaration[indice].execution = deplacement;
                        return 1;
        }   
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = PARAM; // Correspond aux paramètres
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = type;
                table_declaration[indice].execution = deplacement;
                return 1;
            }
        }
        return 0;
    }
    
}

int declaration_procedure(int numero, int type, int numero_region, int indice_representation){
    int vDescription;
    int i;
    int indice;

    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero);
        if (indice != numero){ // Si il doit y avoir débordement 
            
            table_declaration[numero].suivant = indice;
            table_declaration[indice].nature = PROC; // Correspond aux procédures
            table_declaration[indice].suivant = -1;
            table_declaration[indice].region = numero_region;
            table_declaration[indice].description = indice_representation;
            table_declaration[indice].execution = numero_region;
            return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = PROC; // Correspond aux procédures
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = numero_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = numero_region;
                return 1;
            }
        }
    }
    return 0;
}


int declaration_fonction(int numero, int type, int numero_region, int indice_representation){
    int vDescription;
    int i;
    int indice;
    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero);
        if (indice != numero){ // Si il doit y avoir débordement 
                // MAJ de la colonne suivant à l'indice numéro
            table_declaration[numero].suivant = indice;
            table_declaration[indice].nature = FCT; // Correspond aux fonctions
            table_declaration[indice].suivant = -1;
            table_declaration[indice].region = numero_region;
            table_declaration[indice].description = indice_representation;
            table_declaration[indice].execution = numero_region;
            return 1;
            }
        else{ // Pas de débordement, on insère à l'endroit prévu
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = FCT; // Correspond aux fonctions
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = numero_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = numero_region;
                return 1;
            }
        }
    }
    return 0;
}

int gerer_debordement(int numero){
    int i = TAILLE_DEBORDEMENT;
    if (table_lex[numero].suivant != -1){
        // Si il y a un suivant ça veut dire qu'on doit le mettra dans le débordement
        while(i < TAILLE_DECLARATION){ // Tant qu'on a pas modifié l'indice
            if (table_declaration[i].nature != -1){ // Si l'endroit est vide on va l'insérer ici
                return i; // On renvoie i
            }
            i++;
        }
    }
    return numero; // Il n'y a pas de suivant, on retourne le numéro
}

void afficheDeclaration(){
    int i;
    
    printf("\n\tTable des déclarations\n");
    printf("Nature\t| Suivant\t| Région\t| Description\t| Execution\n");
    for (i = 0; i < 50; i++){
        switch(table_declaration[i].nature){
            case 1:
                printf("TYPE_S\t|");
                break;
            case 2:
                printf("TYPE_T\t|");
                break;
            case 3:
                printf("VAR\t|");
                break;
            case 4: 
                printf("PARAM\t|");
                break;
            case 5:
                printf("PROC\t|");
                break;
            case 6:
                printf("FCT\t|");
                break;
            default:
                printf("-1\t|");
                break;
        }
        printf(" %d\t| %d\t| %d\t| %d\n", table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution);
    }
}

/*
int main(){
    init_declaration();
    afficheDeclaration();
    printf("%d\n", TAILLE_DECLARATION);
    exit(EXIT_SUCCESS);
}*/