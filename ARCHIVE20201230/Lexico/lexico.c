#include "lexico.h"

lexeme table_lex[TAILLE_LEXICOGRAPHIQUE];
int hashtab[TAILLE_LEXICOGRAPHIQUE];
int indice = 4; // Les 4 premières cases seront déjà remplies

int hashcode(char* lexeme){ // Calcule le hashcode de la chaine
    int i;
    int caractere = 0;
    for(i=0; i <= strlen(lexeme); i++)
        caractere += lexeme[i];
    return caractere % TAILLE_LEXICOGRAPHIQUE;
}
/* Calcul du hashcode:
    Somme des codes des caractères modulo la longueur de la table des hascodes 
*/

void initialise(){ // Initialisation de la table de hashage à -1 & des 4 premières cases de table_lex
    int i;
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++){
        hashtab[i] = -1;
        table_lex[i].taille = -1;
        strcpy(table_lex[i].contenu, " ");
        table_lex[i].suivant = -1;
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
            return indice-1;
            break;

        default: // Présence d'un élément avec le même hashcode
            while(table_lex[premier].suivant != -1 && strcmp(table_lex[premier].contenu, elem)) // On regarde s'il y a un suivant et si ce n'est pas l'élément
                premier = table_lex[premier].suivant; // On passe à l'élément suivant dans ce cas

            if (strcmp(table_lex[premier].contenu, elem) == 0) // La chaine est déjà présente: On retourne son indice
                return table_lex[premier].taille;


            if (strcmp(table_lex[premier].contenu, elem) != 0){ // La chaine n'est pas présente: On l'ajoute
                table_lex[premier].suivant = indice;
                table_lex[indice].taille = strlen(elem);
                strcpy(table_lex[indice].contenu, elem);
                table_lex[indice].suivant = -1;
                indice++;
                return indice - 1;
        }
        break;      
    }
    return 0;  
}

int num_lexicographique(char *s){ // Renvoie le numéro lexicographique d'un lexème
    int i;
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++){ // Parcours du tableau
        if (strcmp(table_lex[i].contenu, s) == 0){ // Si on est sur la bonne case
            return i; // On retourne son indice (Num lexico)
        }
    }
    return 0; // Sinon on retourne 0 
    // 0 étant le num lex d'un int, on en aura pas besoin (en théorie)
}

void afficheLexico() {
    int i;
    printf("Table lexicographique\n\n");
    printf("Numéro\t|Taille\t|Contenu| Suivant\n");
    for (i = 0; i < indice; i++){
        printf(" %d\t|%d\t|%s\t| %d\n", i, table_lex[i].taille, table_lex[i].contenu, table_lex[i].suivant);
    }
}


void afficheHashcode() {
    int i;
    printf("Table de hachage\n\n");
    for (i = 0; i < indice; i++) {
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

char* itos(int valeur){
    char* arg = malloc(sizeof(char*));
    sprintf(arg, "%d", valeur);
    return arg;
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

void initialise_lex(lexeme table[], int hash[]){ // Initialisation de la table de hashage à -1 & des 4 premières cases de table_lex
    int i;
    for (i = 0; i < TAILLE_LEXICOGRAPHIQUE; i++){
        hash[i] = -1;
        table[i].taille = -1;
        strcpy(table[i].contenu, " ");
        table[i].suivant = -1;
    }
    // Taille
    table[0].taille = strlen("int");
    table[1].taille = strlen("float");
    table[2].taille = strlen("bool");
    table[3].taille = strlen("char");

    // Contenu
    strcpy(table[0].contenu, "int");
    strcpy(table[1].contenu, "float");
    strcpy(table[2].contenu, "bool");
    strcpy(table[3].contenu, "char");

    // Suivant
    table[0].suivant = -1;
    table[1].suivant = -1;
    table[2].suivant = -1;
    table[3].suivant = -1;
}

void insertion(lexeme table[], int hashtable[], char *elem){ // Insertion de l'élément dans la table lexicographique

    int hash = hashcode(elem); // Récupération du hashcode de l'élément
    int premier = hashtab[hash]; // Récupération premier élément

    switch(premier){
        case -1: // Pas d'éléments avec le même hashcode
            table[indice].taille = strlen(elem);
            strcpy(table[indice].contenu, elem);
            table[indice].suivant = -1;
            hashtable[hash] = indice;
            indice++;
            //return indice-1;
            break;

        default: // Présence d'un élément avec le même hashcode
            while(table[premier].suivant != -1 && strcmp(table[premier].contenu, elem)) // On regarde s'il y a un suivant et si ce n'est pas l'élément
                premier = table[premier].suivant; // On passe à l'élément suivant dans ce cas

            if (strcmp(table[premier].contenu, elem) == 0) // La chaine est déjà présente: On retourne son indice
              //  return table_lex[premier].taille;


            if (strcmp(table[premier].contenu, elem) != 0){ // La chaine n'est pas présente: On l'ajoute
                table[premier].suivant = indice;
                table[indice].taille = strlen(elem);
                strcpy(table[indice].contenu, elem);
                table[indice].suivant = -1;
                indice++;
                //return indice - 1;
        }
        break;      
    }
    //return 0; // 
}

void afficheLexicoTable(lexeme table[]) {
    int i;
    printf("Table lexicographique\n\n");
    printf("Numéro\t|Taille\t|Contenu| Suivant\n");
    for (i = 0; i < indice; i++){
        printf(" %d\t|%d\t|%s\t| %d\n", i, table[i].taille, table[i].contenu, table[i].suivant);
    }
}
