#include <stdio.h>
#include <stdlib.h>
#include "darr.h"
#include "estrategia.h"


void crear_arreglo_dinamico(int cant_posiciones_validas) {
    
    DatosTorre* arreglo = malloc(sizeof(DatosTorre) * cant_posiciones_validas);
    return arreglo;
}


void eliminar_arreglo_dinamico(DatosTorre* arreglo) {
    if (arreglo != NULL) {
        free(arreglo);
    }
}