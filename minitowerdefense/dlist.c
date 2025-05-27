#include "dlist.h"

DList* dlist_crear() {
  DList *dlist = malloc(sizeof(DList));
  dlist->primero = NULL;
  dlist->ultimo = NULL;

  return dlist;
}

void dlist_destruir_dnodo(DNodo *lista) {
  DNodo *nodo_a_eliminar;
  while (lista != NULL) {
    nodo_a_eliminar = lista;
    lista = lista->sig;
    free(nodo_a_eliminar);
  }
}

void dlist_destruir(DList *lista) {
  dlist_destruir_dnodo(lista->primero);
  free(lista);
}

int dlist_vacia(DList *lista) {
  return lista->primero == NULL;
}

DList* dlist_agregar_final(DList* lista, int dato) {
  DNodo *nuevo_nodo = malloc(sizeof(DNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = NULL;
  nuevo_nodo->ant = lista->ultimo;

  if (lista->ultimo != NULL)
    lista->ultimo->sig = nuevo_nodo;

  if (lista->primero == NULL)
    lista->primero = nuevo_nodo;

  lista->ultimo = nuevo_nodo;
  return lista;
}

DList* dlist_agregar_inicio(DList *lista, int dato) {
  DNodo *nuevo_nodo = malloc(sizeof(DNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = lista->primero;
  nuevo_nodo->ant = NULL;
  
  if (lista->primero != NULL)
    lista->primero->ant = nuevo_nodo;

  if (lista->ultimo == NULL)
    lista->ultimo = nuevo_nodo;

  lista->primero = nuevo_nodo;
  return lista;
}

void dlist_recorrer_hacia_adelante(DList *lista, FuncionVisitante visit) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

void dlist_recorrer_hacia_atras(DList *lista, FuncionVisitante visit) {
  for (DNodo *nodo = lista->ultimo; nodo != NULL; nodo = nodo->ant)
    visit(nodo->dato);
}