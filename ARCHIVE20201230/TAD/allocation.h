#ifndef _ALLOCATION_H
#define _ALLOCATION_H

/* 
    Programme allocation de L2
*/

#include <stdlib.h>
#include <stdio.h>

// Fonction pour louer de la mémoire
void * allocation_mem(size_t nobjets, size_t taille);
//Version calloc
void * allocation_mem_init0(size_t nobjets, size_t taille);
// Réallocation mémoire
void * reallocation_mem (void **pt, size_t nobjets, size_t taille);
// Libérer mémoire
void libere_mem_peda(void **pt);

#endif