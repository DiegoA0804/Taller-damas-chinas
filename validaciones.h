#ifndef VALIDACIONES_H
#define VALIDACIONES_H

bool dentroDelTablero(int f, int c);
bool esFichaDelJugador(char ficha, char jugador); 
bool movimientoValido(char tablero[8][8], int f1, int c1, int f2, int c2, char jugador);
bool hayFichaParaComer(char tablero[8][8], int f1, int c1, int f2, int c2, char jugador);

#endif
