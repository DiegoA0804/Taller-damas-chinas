#include <iostream>
#include <cmath>
#include "movimientos.h"
#include "validaciones.h"



void coronarSiAplica(char tablero[8][8]) {
    for (int j = 0; j < 8; j++) {
        if (tablero[0][j] == 'B') tablero[0][j] = 'D';  
        if (tablero[7][j] == 'N') tablero[7][j] = 'd'; 
    }
}

bool moverPieza(char tablero[8][8], int f1, int c1, int f2, int c2, char jugador) {
    if (f1 < 0 || f1 >= 8 || c1 < 0 || c1 >= 8 || f2 < 0 || f2 >= 8 || c2 < 0 || c2 >= 8) {
        std::cout << "Movimiento fuera del tablero.\n";
        return false;
    }

    if (!movimientoValido(tablero, f1, c1, f2, c2, jugador))
        return false;

    if (std::abs(f2 - f1) == 2 && !hayFichaParaComer(tablero, f1, c1, f2, c2, jugador))
        return false;

    char pieza = tablero[f1][c1];
    int dx = f2 - f1;
    int dy = c2 - c1;

    if (std::abs(dx) == 1 && std::abs(dy) == 1) {
        tablero[f2][c2] = pieza;
        tablero[f1][c1] = ' ';
        coronarSiAplica(tablero);
        return true;
    }

    if (std::abs(dx) == 2 && std::abs(dy) == 2) {
        int fMedio = f1 + dx / 2;
        int cMedio = c1 + dy / 2;
        char enemigo = (jugador == 'B') ? 'N' : 'B';
        char enemigoDama = (jugador == 'B') ? 'd' : 'D';

        if (tablero[fMedio][cMedio] == enemigo || tablero[fMedio][cMedio] == enemigoDama) {
            tablero[f2][c2] = pieza;
            tablero[f1][c1] = ' ';
            tablero[fMedio][cMedio] = ' ';
            coronarSiAplica(tablero);
            return true;
        }
    }

    std::cout << "Movimiento no valido.\n";
    return false;
}

bool puedeSeguirCapturando(char tablero[8][8], int fila, int col, char jugador) {
    int direcciones[2] = {-1, 1};
    char enemigo = (jugador == 'B') ? 'N' : 'B';
    char enemigoDama = (jugador == 'B') ? 'd' : 'D';

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int dx = direcciones[i];
            int dy = direcciones[j];
            int fMedio = fila + dx;
            int cMedio = col + dy;
            int fDestino = fila + 2 * dx;
            int cDestino = col + 2 * dy;

            if (fDestino >= 0 && fDestino < 8 && cDestino >= 0 && cDestino < 8) {
                if ((tablero[fMedio][cMedio] == enemigo || tablero[fMedio][cMedio] == enemigoDama) &&
                    tablero[fDestino][cDestino] == ' ') {
                    return true;
                }
            }
        }
    }
    return false;
}