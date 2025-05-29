#ifndef PILA_H
#define PILA_H

#include "estrategia.h"
#include "pila.h"
#include "torre.h"

typedef struct SNodo {
    DatosTorre dato;
    struct SNodo* siguiente;
} SNodo;


typedef struct Pila {
    SNodo* cabeza;
    int tamano;
} Pila;

typedef void (*FuncionVisitante)(DatosTorre dato);

Pila* crear_pila();

void destruir_pila(Pila* pila);

void apilar(Pila* pila, DatosTorre dato);

DatosTorre desapilar(Pila* pila);

int esta_vacia(Pila* pila);

int obtener_tamano(Pila* pila);

DatosTorre cima(Pila* pila);

void recorrer_pila(Pila* pila, FuncionVisitante visit);

#endif
