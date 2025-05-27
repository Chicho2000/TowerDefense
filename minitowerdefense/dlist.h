//Esto pregunta si está definida la librería, en caso de no
//estarlo la define
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _DNodo {
  int dato;
  struct _DNodo *sig;
  struct _DNodo *ant;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
} DList;


DList* dlist_crear();


void dlist_destruir_dnodo(DNodo *lista);


void dlist_destruir(DList *lista);


int dlist_vacia(DList *lista);


DList* dlist_agregar_final(DList* lista, int dato);


DList* dlist_agregar_inicio(DList *lista, int dato);


void dlist_recorrer_hacia_adelante(DList *lista, FuncionVisitante visit);


void dlist_recorrer_hacia_atras(DList *lista, FuncionVisitante visit);

#endif 
