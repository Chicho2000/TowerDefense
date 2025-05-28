#ifndef PILA_H
#define PILA_H


typedef struct SNodo {
    DatosTorre dato;
    struct SNodo* siguiente;
} SNodo;


typedef struct Pila {
    SNodo* cabeza;
    int tamaño;
} Pila;

typedef void (*FuncionVisitante)(DatosTorre dato);

Pila* crear_pila();

void destruir_pila(Pila* pila);

void apilar(Pila* pila, DatosTorre dato);

int desapilar(Pila* pila);

int esta_vacia(Pila* pila);

int obtener_tamano(Pila* pila);

int cima(Pila* pila);

void recorrer_pila(Pila* pila, FuncionVisitante visit);

#endif