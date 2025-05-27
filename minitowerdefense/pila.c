#include <stdio.h>
#include <stdlib.h>
#include "pila.h"


Pila* crear_pila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    if (pila == NULL) {
        printf("Error: No se pudo asignar memoria para la pila.\n");
        exit(1);
    }
    pila->cabeza = NULL;
    pila->tamaño = 0;
    return pila;
}


void destruir_pila(Pila* pila) {
    SNodo* actual = pila->cabeza;
    while (actual != NULL) {
        SNodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(pila);
}


void apilar(Pila* pila, int dato) {
    SNodo* nuevo = (SNodo*)malloc(sizeof(SNodo));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria para el nodo.\n");
        exit(1);
    }
    nuevo->dato = dato;
    nuevo->siguiente = pila->cabeza;
    pila->cabeza = nuevo;
    pila->tamaño++;
}


int desapilar(Pila* pila) {
    if (esta_vacia(pila)) {
        printf("Error: La pila está vacía.\n");
        exit(1);
    }
    SNodo* temp = pila->cabeza;
    int dato = temp->dato;
    pila->cabeza = pila->cabeza->siguiente;
    free(temp);
    pila->tamaño--;
    return dato;
}


int esta_vacia(Pila* pila) {
    return pila->tamaño == 0;
}


int obtener_tamano(Pila* pila) {
    return pila->tamaño;
}


int cima(Pila* pila) {
    if (esta_vacia(pila)) {
        printf("Error: La pila está vacía.\n");
        exit(1);
    }
    return pila->cabeza->dato;
}


void recorrer_pila(Pila* pila, FuncionVisitante visit) {
    for (Nodo* nodo = pila->cabeza; nodo != NULL; nodo = nodo->siguiente) {
        visit(nodo->dato);
    }
}