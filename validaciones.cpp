#include <iostream>
#include <cmath>
#include "validaciones.h"


bool dentroDelTablero(int f, int c) {
    return (f >= 0 && f < 8 && c >= 0 && c < 8);
}

bool esFichaDelJugador(char ficha, char jugador) {
    if (jugador == 'X') return (ficha == 'X' || ficha == 'K'); 
    if (jugador == 'O') return (ficha == 'O' || ficha == 'k'); 
    return false;
}

bool movimientoValido(char tablero[8][8], int f1, int c1, int f2, int c2, char jugador) {
    if (!dentroDelTablero(f1, c1) || !dentroDelTablero(f2, c2)) {
        std::cout << "Movimiento fuera del tablero.\n";
        return false;
    }

    char ficha = tablero[f1][c1];

    if (!esFichaDelJugador(ficha, jugador)) {
        std::cout << " Esa ficha no es tuya.\n";
        return false;
    }

    if (tablero[f2][c2] != ' ') {
        std::cout << " La casilla está ocupada.\n";
        return false;
    }

    int dx = f2 - f1;
    int dy = std::abs(c2 - c1);

    if (std::abs(dx) == 1 && dy == 1) {
        if (ficha == 'X' && dx == 1) return true;  
        if (ficha == 'O' && dx == -1) return true; 
        if (ficha == 'K' || ficha == 'k') return true; 
        std::cout << " Movimiento no valido en esa dirección.\n";
        return false;
    }

    if (std::abs(dx) == 2 && dy == 2)
        return true; 

    std::cout << " Movimiento inválido.\n";
    return false;
}

bool hayFichaParaComer(char tablero[8][8], int f1, int c1, int f2, int c2, char jugador) {
    int dx = f2 - f1;
    int dy = c2 - c1;
    if (std::abs(dx) != 2 || std::abs(dy) != 2) return false;

    int fMedio = f1 + dx / 2;
    int cMedio = c1 + dy / 2;

    char enemigo = (jugador == 'X') ? 'O' : 'X';
    char enemigoDama = (jugador == 'X') ? 'k' : 'K';
    char fichaEnMedio = tablero[fMedio][cMedio];

    if (fichaEnMedio == enemigo || fichaEnMedio == enemigoDama) return true;

    std::cout << " No hay una ficha para comer.\n";
    return false;
}