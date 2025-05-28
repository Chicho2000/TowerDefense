#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include "mapa.h"
#include "nivel.h"

typedef void (*DisposicionTorres)(Nivel*, Mapa*);

typedef struct  t{
    Coordenada posicion;
    int cant_casillas_en_rango;
} DatosTorre;

void disponer(Nivel* nivel, Mapa* mapa);

void disponer_con_backtracking(Nivel* nivel, Mapa* mapa);

void disponer_custom(Nivel* nivel, Mapa* mapa);

#endif
