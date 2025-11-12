#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H


bool moverPieza(char tablero[8][8], int f1, int c1, int f2, int c2, char jugador);


bool puedeSeguirCapturando(char tablero[8][8], int fila, int col, char jugador);


void coronarSiAplica(char tablero[8][8]);

#endif