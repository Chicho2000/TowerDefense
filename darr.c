#include <stdio.h>
#include <stdlib.h>
#include "darr.h"

DatosTorre* crear_arreglo_dinamico(int cantidad) {
    DatosTorre* arreglo = (DatosTorre*)malloc(cantidad * sizeof(DatosTorre));

    return arreglo;
}

void eliminar_arreglo_dinamico(DatosTorre* arreglo) {
    if (arreglo != NULL) {
        free(arreglo);
    }
}
