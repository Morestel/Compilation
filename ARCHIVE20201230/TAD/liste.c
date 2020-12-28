#include "liste.h"

liste liste_vide(){
    return NULL;
}

int est_liste_vide(liste l){
    if (l==liste_vide())
        return 1;

    return 0;
}

liste inserer_element_liste(liste l, element elem){
    liste lnew=(liste)allocation_mem(1, sizeof(struct_cellule));
    lnew->objet=elem;
    lnew->suivant=l;
    return lnew;
}

element renvoie_premier_liste(liste l){
    if (est_liste_vide(l))
        printf("La liste est vide\n");
    return l->objet;
}

liste supprimer_premier_liste(liste l){
    liste lsuivant=l->suivant;
    free(l);
    return lsuivant;
}