#include "allocation.h"

void * allocation_mem(size_t nobjets, size_t taille)
{
    void * pt;
    pt = malloc (nobjets * taille); // Allocation, on vérifie si elle marche
    if (pt == NULL)
        printf("Impossible d'allouer la mémoire %ld %ld\n", nobjets, taille);
    return (pt);
}

void * allocation_mem_init0(size_t nobjets, size_t taille)
{
    void *pt;
    pt = calloc (nobjets, taille);
    if (pt==NULL)
        printf("Impossible d'allouer la mémoire %ld * %ld\n", nobjets, taille);
    return pt;
}

void * reallocation_mem (void **pt, size_t nobjets, size_t taille)
{
    void *pt_realloc = realloc(*pt, nobjets*taille);
    if (pt_realloc != NULL)
        *pt = pt_realloc;
    else
        printf("Impossible de reallouer la mémoire %ld * %ld a l'adresse %p\n", nobjets, taille, *pt);
    return pt_realloc;
}

void libere_mem_peda(void **pt)
{
    if ((*pt)!=NULL)
        free(*pt);
    *pt=NULL;
}