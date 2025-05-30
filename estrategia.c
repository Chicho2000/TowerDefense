#include "estrategia.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "pila.h"
#include "darr.h"

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
    int cant_torres, int vida_objetivo,
    Pila* torres
) {
    int indices[cant_torres];
    int nivel_back = 0;
    int suma_actual = 0;

    for (int i = 0; i < cant_torres; i++) indices[i] = -1;

    int i = 0;
    while (nivel_back >= 0) {
        if (nivel_back == cant_torres) {
            // Solución encontrada
            if (suma_actual >= vida_objetivo)
                return 1;
            // Retroceder
            nivel_back--;
            if (nivel_back >= 0) {
                suma_actual -= datos_torres[indices[nivel_back]].cant_casillas_en_rango;
                desapilar(torres);
                i = indices[nivel_back] + 1;
            }
            continue;
        }

        if (i >= cant_validas) {
            // No hay más opciones en este nivel, retroceder
            nivel_back--;
            if (nivel_back >= 0) {
                suma_actual -= datos_torres[indices[nivel_back]].cant_casillas_en_rango;
                desapilar(torres);
                i = indices[nivel_back] + 1;
            }
            continue;
        }

        // Apilar torre y avanzar
        indices[nivel_back] = i;
        apilar(torres, datos_torres[i]);
        suma_actual += datos_torres[i].cant_casillas_en_rango;
        nivel_back++;
        i = (nivel_back == 0) ? 0 : indices[nivel_back - 1] + 1;
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
    mapa->cant_torres,
    nivel->enemigos->vida_inicial,
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

static void comparar_torres(DatosTorre* arr, int left, int right) {
    if (left >= right) return;

    int i = left, j = right;
    int pivot = arr[(left + right) / 2].cant_casillas_en_rango;

    while (i <= j) {
        while (arr[i].cant_casillas_en_rango > pivot) i++;
        while (arr[j].cant_casillas_en_rango < pivot) j--;
        if (i <= j) {
            // Intercambiar arr[i] y arr[j]
            DatosTorre temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) comparar_torres(arr, left, j);
    if (i < right) comparar_torres(arr, i, right);
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int cant_validas = posiciones_validas(
        posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho
    );

    DatosTorre* arr_torres = crear_arreglo_dinamico(cant_validas);

    // Guardar todas las posiciones válidas con su cant_casillas_en_rango
    for (int i = 0; i < cant_validas; i++) {
        arr_torres[i].posicion = posiciones_validas_torre[i];
        arr_torres[i].cant_casillas_en_rango = camino_dentro_del_rango(
            &posiciones_validas_torre[i],
            mapa->casillas,
            mapa->distancia_ataque,
            mapa->alto,
            mapa->ancho
        );
    }

    // Ordenar el arreglo de mayor a menor por cant_casillas_en_rango
    comparar_torres(arr_torres, 0, cant_validas - 1);

    // Colocar las torres en las mejores posiciones
    for (int t = 0; t < mapa->cant_torres; t++) {
        colocar_torre(mapa, arr_torres[t].posicion.x, arr_torres[t].posicion.y, t);
    }

    eliminar_arreglo_dinamico(arr_torres);
}
