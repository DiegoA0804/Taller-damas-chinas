#ifndef JUEGO_H
#define JUEGO_H

bool hayMovimientosDisponibles(char tablero[8][8], char jugador);
bool tienePiezas(char tablero[8][8], char jugador);
bool juegoTerminado(char tablero[8][8], char jugador);
void jugar(bool contraIA);

#endif