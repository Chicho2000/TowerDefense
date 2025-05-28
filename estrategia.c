#include "estrategia.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "pila.h"

static int posiciones_validas(Coordenada *validas, TipoCasilla **casillas, int alto, int ancho) {
    int cant_posiciones_validas = 0;
    
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (casillas[i][j] == VACIO) {
                validas[cant_posiciones_validas].x = i;
                validas[cant_posiciones_validas++].y = j;
            }
        }
    }

    return cant_posiciones_validas;
}

static int camino_dentro_del_rango(Coordenada *cord_torre, TipoCasilla **casillas, int rango, int alto, int ancho) {
    int cant_camino = 0;
    
    for(int i = (cord_torre->x - rango); i <= (cord_torre->x + rango) && i < alto; i++) {
        for(int j = (cord_torre->y - rango); j <= (cord_torre->y + rango) && j < ancho; j++) { 
            if (casillas[i][j] == CAMINO)
                cant_camino++;
        }
    }
    
    return;
}

static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = TORRE;
}

static int determinar_posicion_torre(int *casilla_elegida, int cant_validas) {
    int nueva_posicion = rand() % cant_validas;
    while(casilla_elegida[nueva_posicion])
        nueva_posicion = rand() % cant_validas;

    return nueva_posicion;
}


void disponer(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int casilla_elegida[cantidad_casillas];
    for(int i = 0; i < cantidad_casillas; casilla_elegida[i++] = 0);

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre = determinar_posicion_torre(casilla_elegida, cant_validas);
        casilla_elegida[nueva_torre] = 1;
        int nueva_torre_x = posiciones_validas_torre[nueva_torre].x;
        int nueva_torre_y = posiciones_validas_torre[nueva_torre].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
}


void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {

    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);
    Pila* torres = crear_pila();

    for (int i = 0; i < cant_validas; i++) {
        DatosTorre torre[cant_validas];
        torre[i].posicion = posiciones_validas_torre[i];
        torre[i].cant_casillas_en_rango = camino_dentro_del_rango(
            &posiciones_validas_torre[i],
            mapa->casillas,
            mapa->distancia_ataque,
            mapa->alto,
            mapa->ancho
        );
    }

    int indices[mapa->cant_torres];
    int encontrado = backtracking_torres(
        torre, 
        cant_validas, 
        indices, 
        0, 
        mapa->cant_torres, 
        0, 
        nivel->enemigos->vida_inicial
    );

    if (encontrado) {
        // Colocar las torres en el mapa según la combinación encontrada
        for (int t = 0; t < mapa->cant_torres; t++) {
            int x = torre[indices[t]].posicion.x;
            int y = torre[indices[t]].posicion.y;
            colocar_torre(mapa, x, y, t);
        }
    } else {
        printf("No se encontró una combinación válida de torres.\n");
    }    

    destruir_pila(torres);

    return;
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}
