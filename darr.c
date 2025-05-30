#include <stdio.h>
#include <stdlib.h>
#include "darr.h"
#include "estrategia.h"


DatosTorre* crear_arreglo_dinamico(int cantidad) {
    DatosTorre* arreglo = (DatosTorre*)malloc(cantidad * sizeof(DatosTorre));
    if (arreglo == NULL) {
        printf("Error al asignar memoria para el arreglo dinámico.\n");
        exit(1);
    }
    return arreglo;
}

void eliminar_arreglo_dinamico(DatosTorre* arreglo) {
    if (arreglo != NULL) {
        free(arreglo);
    }
}