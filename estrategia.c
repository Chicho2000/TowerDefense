#include "estrategia.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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

static int backtracking_torres(
    DatosTorre* datos_torres, int cant_validas,
    int nivel_actual, int cant_torres,
    int suma_actual, int vida_objetivo,
    int inicio,
    Pila* torres
) {
    if (nivel_actual == cant_torres) {
        return suma_actual >= vida_objetivo;
    }

    for (int i = inicio; i < cant_validas; i++) {
        apilar(torres, datos_torres[i]);
        int nueva_suma = suma_actual + datos_torres[i].cant_casillas_en_rango;
        if (backtracking_torres(datos_torres, cant_validas, nivel_actual + 1, cant_torres, nueva_suma, vida_objetivo, i + 1, torres)) {
            return 1;
        }
        desapilar(torres); //desapilo parea probar otra opcion
    }
    return 0;
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

    DatosTorre torre[cant_validas];

    for (int i = 0; i < cant_validas; i++) {
        torre[i].posicion = posiciones_validas_torre[i];
        torre[i].cant_casillas_en_rango = camino_dentro_del_rango(
            &posiciones_validas_torre[i],
            mapa->casillas,
            mapa->distancia_ataque,
            mapa->alto,
            mapa->ancho
        );
    }

    int encontrado = backtracking_torres(
        torre,
        cant_validas,
        0,
        mapa->cant_torres,
        0,
        nivel->enemigos->vida_inicial,
        0,
        torres
    );

     if (encontrado) {
        // Colocar las torres en el mapa según la pila (de arriba hacia abajo)
        int t = mapa->cant_torres - 1;
        while (!esta_vacia(torres)) {
            DatosTorre torre_colocada = desapilar(torres);
            colocar_torre(mapa, torre_colocada.posicion.x, torre_colocada.posicion.y, t);
            t--;
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
