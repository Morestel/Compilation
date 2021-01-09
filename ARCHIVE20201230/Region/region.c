#include "region.h"

region table_reg[TAILLE_REGION];
pile pile_region;

void init_region(){
    int i;
    for (i = 0; i < TAILLE_REGION; i++){
        table_reg[i].taille = 0;
        table_reg[i].nis = -1;
        table_reg[i].arbre_r = NULL;
    }
}

int nombre_region(){
    int i;
    int nombre = 0;
    for (i = 0; i < TAILLE_REGION; i++){
        if (table_reg[i].nis != -1)
            nombre++;
    }
    return nombre;
}

void ajoutRegion(int newTaille, int newNis, arbre newArbre){
    int nombre = nombre_region();
   
    if (nombre >= TAILLE_REGION){
        perror("Taille maximale atteinte");
        exit(EXIT_FAILURE);
    }
    table_reg[nombre].taille = newTaille;
    table_reg[nombre].nis = newNis;
    table_reg[nombre].arbre_r = newArbre;
}

void ajout_arbre_region(int i, arbre newArbre){
    table_reg[i].arbre_r = newArbre;
}

void affiche_region(){ // Par soucis de place on n'affiche pas les arbres
    int i;
    int nombre = nombre_region();
    printf("\n-----Table des régions-----\n");
    printf("Taille\t| NIS\t| Arbre\n");
    for (i=0 ; i< nombre; i++)
        printf("%d\t| %d\t|\n",table_reg[i].taille, table_reg[i].nis);

}


/*
int main(){
    init_region();
    // Exemple de la fiche du cours
    ajoutRegion(38, 0, NULL);
    ajoutRegion(2, 1, NULL);
    ajoutRegion(4, 2, NULL);
    ajoutRegion(4, 3, NULL);
    ajoutRegion(5, 3, NULL);
    ajoutRegion(2, 0, NULL);
    ajoutRegion(3, 1, NULL);
    ajoutRegion(4, 2, NULL);
    ajoutRegion(3, 1, NULL);
    ajoutRegion(3, 1, NULL);
    affiche(table_reg);
    exit(EXIT_SUCCESS);  
}*/