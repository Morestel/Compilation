#include "lexico.h"

lexeme table_lex[TAILLE_LEXICOGRAPHIQUE];
int hashtab[TAILLE_HASHCODE];
int indice = 0; 


int hashcode(char* lexeme){ // Calcule le hashcode de la chaine
    int i;
    int caractere = 0;
    for(i=0; i <= strlen(lexeme); i++)
        caractere += lexeme[i];
    return caractere % (TAILLE_HASHCODE+1);
}
/* Calcul du hashcode:
    Somme des codes des caractères modulo la longueur de la table des hascodes 
*/

void initialise(){ // Initialisation de la table de hashage à -1 & des 4 premières cases de table_lex
    int i;
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++){
        table_lex[i].taille = -1;
        strcpy(table_lex[i].contenu, " ");
        table_lex[i].suivant = -1;
    }

    for (i = 0; i < TAILLE_HASHCODE; i++){
        hashtab[i] = -1;
    }
    // Taille
    table_lex[0].taille = strlen("int");
    table_lex[1].taille = strlen("float");
    table_lex[2].taille = strlen("bool");
    table_lex[3].taille = strlen("char");

    // Contenu
    strcpy(table_lex[0].contenu, "int");
    strcpy(table_lex[1].contenu, "float");
    strcpy(table_lex[2].contenu, "bool");
    strcpy(table_lex[3].contenu, "char");

    // Suivant
    table_lex[0].suivant = -1;
    table_lex[1].suivant = -1;
    table_lex[2].suivant = -1;
    table_lex[3].suivant = -1;

    indice = 4;
}

int inserer_lexicographique(char *elem){ // Insertion de l'élément dans la table lexicographique
    
    int hash = hashcode(elem); // Récupération du hashcode de l'élément
    int premier = hashtab[hash]; // Récupération premier élément
    
    switch(premier){
        case -1: // Pas d'éléments avec le même hashcode
            table_lex[indice].taille = strlen(elem);
            strcpy(table_lex[indice].contenu, elem);
            table_lex[indice].suivant = -1;
            hashtab[hash] = indice;
            indice++;
            return 1; // Insertion réussie
            break;

        default: // Présence d'un élément avec le même hashcode
            // On va chercher lequel n'a pas de suivant
            
            if (strcmp(table_lex[premier].contenu, elem) == 0){ // Si l'élément est déjà dedans
                    return 0;
            }
            while(table_lex[premier].suivant != -1){
                if (strcmp(table_lex[premier].contenu, elem) == 0){ // Si l'élément est déjà dedans
                    return 0;
                }
                premier = table_lex[premier].suivant;
            }

            
             // La chaine n'est pas présente: On l'ajoute à l'indice premier
                table_lex[premier].suivant = indice; // On vient d'ajouter le suivant
                table_lex[indice].taille = strlen(elem);
                strcpy(table_lex[indice].contenu, elem);
                table_lex[indice].suivant = -1;
                indice++;
                return 1; // Insertion réussie
        
        break;      
    }
    return 0; // Echec de l'insertion on renvoie 0
}

void afficheLexico() {
    int i;
    printf("Table lexicographique\n\n");
    printf("Numéro\t|Taille\t|Contenu| Suivant\n");
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++){
        if (table_lex[i].taille != -1){
            printf(" %d\t|%d\t|%s\t| %d\n", i, table_lex[i].taille, table_lex[i].contenu, table_lex[i].suivant);
        }
    }
}


void afficheHashcode() {
    int i;
    printf("Table de hachage\n\n");
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++) {
        printf("%d\n", hashtab[i]);
    }
}
// Etant donné un lexème, on renvoie son numéro de déclaration (L'indice de la table des lexèmes concorde avec celui de la table des déclarations)
int association_nom(char *lexeme){
    int i;
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++){ // Parcours de la table à la recherche du lexème
        if (strcmp(lexeme, table_lex[i].contenu) == 0){ // Ca veut dire qu'on l'a trouvé
            return i; // On retourne l'indice
        }
    }
    return -1; // On ne l'a pas trouvé, on retourne -1 (car 0 est pris par int)
}







/*
// Fonction pour test 
int main(int argc, char *argv[]){
    int h = hashcode("45aifofe");
    int i;
    printf("%d\n", h);
    initialise();
    afficheLexico(table_lex);
    // Insertion
    for (i = 1; i < argc; i++)
        inserer_lexicographique(argv[i]);
        
    // Affichage tab
    afficheHashcode();

    // Affichage tablelex
    afficheLexico();

    return 1;
}*/

