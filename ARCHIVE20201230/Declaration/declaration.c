#include "declaration.h"

extern int representation[TAILLE_REPRESENTATION];
extern region table_reg[TAILLE_REGION];
lexeme table_lex[TAILLE_LEXICOGRAPHIQUE];
declaration table_declaration[TAILLE_DECLARATION];

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
        if (table_declaration[numero].nature != -1){ // Si il doit y avoir débordement 
            
                i = TAILLE_DEBORDEMENT;
            while (i < TAILLE_DECLARATION && table_declaration[i].nature == -1){
                i++;
            }
            table_declaration[i].nature = TYPE_S; // Correspond aux fonctions
            table_declaration[i].suivant = -1;
            table_declaration[i].region = num_region;
            table_declaration[i].description = indice_representation;
            table_declaration[i].execution = type;
            table_declaration[indice].suivant = i;
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
        if (table_declaration[numero].nature != -1){ // Si il doit y avoir débordement 
            
             i = TAILLE_DEBORDEMENT;
            while (i < TAILLE_DECLARATION && table_declaration[i].nature == -1){
                i++;
            }
            table_declaration[i].nature = TYPE_T; // Correspond aux fonctions
            table_declaration[i].suivant = -1;
            table_declaration[i].region = num_region;
            table_declaration[i].description = indice_representation;
            table_declaration[i].execution = nombre_dimensions * type + type;
            table_declaration[indice].suivant = i;
            nb_declaration++;

                return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = TYPE_T; // Correspond aux tableaux
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = nombre_dimensions * type + type;
                nb_declaration++;
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
        
        if (table_declaration[numero].nature != -1){ // Si il doit y avoir débordement 
            printf("Mise à jour\n");
            i = TAILLE_DEBORDEMENT;
            while (i < TAILLE_DECLARATION && table_declaration[i].nature != -1){
                i++;
            }
            
            table_declaration[i].nature = VAR; // Correspond aux fonctions
            table_declaration[i].suivant = -1;
            table_declaration[i].region = num_region;
            table_declaration[i].description = type;
            table_declaration[i].execution = deplacement;
            table_declaration[indice].suivant = i;
            nb_declaration++;
            return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = VAR; // Correspond aux variables
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = type;
                table_declaration[indice].execution = deplacement;
                nb_declaration++;
                return 1;
            }
        }
    }
    return 0;
}


int declaration_parametre(int numero, int type, int deplacement, int num_region){
    int i;
    int indice;

    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero); // Indice n'a soit pas bouger soit il contient l'endroit du prochain élément à insérer dans débordement
        if (table_declaration[numero].nature != -1){ // Si il doit y avoir débordement 
             i = TAILLE_DEBORDEMENT;
            while (i < TAILLE_DECLARATION && table_declaration[i].nature == -1){
                i++;
            }
            table_declaration[i].nature = PARAM; // Correspond aux fonctions
            table_declaration[i].suivant = -1;
            table_declaration[i].region = num_region;
            table_declaration[i].description = type;
            table_declaration[i].execution = deplacement;
            table_declaration[indice].suivant = i;
            nb_declaration++;
        }   
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = PARAM; // Correspond aux paramètres
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = num_region;
                table_declaration[indice].description = type;
                table_declaration[indice].execution = deplacement;
                nb_declaration++;
                return 1;
            }
        }
        return 0;
    }
    
}

int declaration_procedure(int numero, int type, int numero_region, int indice_representation){
    int i;
    int indice;

    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero);
        if (table_declaration[numero].nature != -1){ // Si il doit y avoir débordement 
            
            i = TAILLE_DEBORDEMENT;
            while (i < TAILLE_DECLARATION && table_declaration[i].nature == -1){
                i++;
            }
            table_declaration[i].nature = PROC; // Correspond aux fonctions
            table_declaration[i].suivant = -1;
            table_declaration[i].region = numero_region;
            table_declaration[i].description = indice_representation;
            table_declaration[i].execution = numero_region;
            table_declaration[indice].suivant = i;
            nb_declaration++;
            return 1;
        }
        else{
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = PROC; // Correspond aux procédures
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = numero_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = numero_region;
                nb_declaration++;
                return 1;
            }
        }
    }
    return 0;
}


int declaration_fonction(int numero, int type, int numero_region, int indice_representation){
    int i;
    int indice;
    if (nb_declaration >= TAILLE_DEBORDEMENT)
        printf("Plus d'espace dans la table des déclarations\n");
    else{
        // On commence par gérer le débordement
        indice = gerer_debordement(numero); // Indice: 2 valeurs possibles: - Numero car pas de suivant | - L'indice du dernier suivant (Pour mettre à jour son champ suivant)
        if (table_declaration[numero].nature != -1){ // Si il doit y avoir débordement 
            
            i = TAILLE_DEBORDEMENT;
            while (i < TAILLE_DECLARATION && table_declaration[i].nature == -1){
                i++;
            }
            table_declaration[i].nature = FCT; // Correspond aux fonctions
            table_declaration[i].suivant = -1;
            table_declaration[i].region = numero_region;
            table_declaration[i].description = indice_representation;
            table_declaration[i].execution = numero_region;
            table_declaration[indice].suivant = i;
            nb_declaration++;
            return 1;
            }
        else{ // Pas de débordement, on insère à l'endroit prévu
            if (table_declaration[indice].nature == -1){ // Rien à cet endroit, on l'insère ici
                table_declaration[indice].nature = FCT; // Correspond aux fonctions
                table_declaration[indice].suivant = -1;
                table_declaration[indice].region = numero_region;
                table_declaration[indice].description = indice_representation;
                table_declaration[indice].execution = numero_region;
                nb_declaration++;
                return 1;
            }
        }
    }
    return 0;
}

int gerer_debordement(int numero){
    if (table_declaration[numero].nature != -1){ // S'il y a déjà quelque chose ici 
        while (table_declaration[numero].suivant != -1){ // On regarde les suivants jusqu'à ce qu'il n'y en ai plus
            numero = table_declaration[numero].suivant;
        }
    }
    return numero;
}

void afficheDeclaration(){
    int i;
    
    printf("\n\tTable des déclarations\n");
    printf("Indice\t| Nature\t| Suivant\t| Région\t| Description\t| Execution\n");
    for (i = 0; i < 50; i++){
        printf("%d\t| ", i);
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

void afficheDebordement(){
    int i;
    
    printf("\n\tTable des débordements\n");
    printf("Indice\t| Nature\t| Suivant\t| Région\t| Description\t| Execution\n");
    for (i = TAILLE_DEBORDEMENT; i < TAILLE_DEBORDEMENT + 50; i++){
        printf("%d\t| ", i);
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