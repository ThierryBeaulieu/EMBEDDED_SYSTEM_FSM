/*
 * Travail : TP7
 * Auteurs : Thierry Beaulieu, Tuan Quoc Pham, Sara Beddouch et Karim El Hosni
 * Section # : 02
 * Équipe # : 2126
 * Description: Implemente les jetons new et delete pour l'utilisation de pointeur dans les classes
*/

#include <stddef.h>
#include <stdlib.h>

void * operator new(size_t size){
    return malloc(size);
}

void operator delete(void * ptr){
    free(ptr);
}