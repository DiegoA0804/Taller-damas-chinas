#include "juego.h"
#include "ia.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#define RESET   "\033[0m"
#define NEGRO   "\033[30m"
#define ROJO    "\033[31m"
#define AMARILLO "\033[33m"
#define BLANCO  "\033[97m"
#define FONDO_OSCURO "\033[48;5;235m"
#define FONDO_CLARO  "\033[48;5;240m"

void mostrarTablero(char tablero[8][8]) {
    std::cout << "\n    a  b  c  d  e  f  g  h\n";
    std::cout << "   ------------------------\n";

    for (int i = 0; i < 8; i++) {
        std::cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++) {
            bool casillaOscura = ((i + j) % 2 == 1);
            std::string fondo = casillaOscura ? FONDO_OSCURO : FONDO_CLARO;
            char ficha = tablero[i][j];
            std::string colorFicha;

            switch (ficha) {
                case 'X': colorFicha = BLANCO; break;
                case 'O': colorFicha = ROJO; break;
                default: colorFicha = ""; break;
            }

            if (ficha == ' ')
                std::cout << fondo << "   " << RESET;
            else
                std::cout << fondo << colorFicha << " " << ficha << " " << RESET;
        }
        std::cout << " |" << i + 1 << "\n";
    }

    std::cout << "   ------------------------\n";
    std::cout << "    a  b  c  d  e  f  g  h\n\n";
}

void inicializarTablero(char tablero[8][8]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            tablero[i][j] = ' ';

    for (int i = 0; i < 3; i++)
        for (int j = (i + 1) % 2; j < 8; j += 2)
            tablero[i][j] = 'X';

    for (int i = 5; i < 8; i++)
        for (int j = (i + 1) % 2; j < 8; j += 2)
            tablero[i][j] = 'O';
}

void contarFichas(char tablero[8][8], int &fichasX, int &fichasO) {
    fichasX = 0;
    fichasO = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (tablero[i][j] == 'X') fichasX++;
            if (tablero[i][j] == 'O') fichasO++;
        }
}

bool puedeMoverFicha(char tablero[8][8], int f, int c) {
    if (tablero[f][c] != 'X' && tablero[f][c] != 'O') return false;

    int dir = (tablero[f][c] == 'X') ? 1 : -1; 
    int direcciones[2][2] = {{dir, 1}, {dir, -1}};

    // 🔁 For normal en lugar del for-each
    for (int i = 0; i < 2; i++) {
        int nf = f + direcciones[i][0];
        int nc = c + direcciones[i][1];
        int cf = f + 2 * direcciones[i][0];
        int cc = c + 2 * direcciones[i][1];

        if (nf >= 0 && nf < 8 && nc >= 0 && nc < 8 && tablero[nf][nc] == ' ')
            return true;

        if (cf >= 0 && cf < 8 && cc >= 0 && cc < 8 &&
            tablero[nf][nc] != ' ' && tablero[cf][cc] == ' ') {
            if ((tablero[f][c] == 'X' && tablero[nf][nc] == 'O') ||
                (tablero[f][c] == 'O' && tablero[nf][nc] == 'X'))
                return true;
        }
    }
    return false;
}

void jugar(bool contraIA) {
    char tablero[8][8];
    inicializarTablero(tablero);

    bool turnoJugador1 = true;

    while (true) {
        mostrarTablero(tablero);

        int fichasX, fichasO;
        contarFichas(tablero, fichasX, fichasO);

        if (fichasX == 0) {
            std::cout << "\n¡El jugador 2 ganó!" << (contraIA ? " Computadora \n" : "\n");
            break;
        }
        if (fichasO == 0) {
            std::cout << "\n¡El Jugador 1 ganó! \n";
            break;
        }

        if (turnoJugador1) {
            std::cout << "\nLe toca al jugador 1 (X)\n";
            std::string origen, destino;

            std::cout << "Qué ficha quieres mover: ";
            std::cin >> origen;

            if (origen.size() != 2) {
                std::cout << "Formato incorrecto.\n";
                continue;
            }

            int c1 = origen[0] - 'a';
            int f1 = origen[1] - '1';

            if (f1 < 0 || f1 > 7 || c1 < 0 || c1 > 7) {
                std::cout << "Coordenada fuera del tablero.\n";
                continue;
            }

            if (tablero[f1][c1] != 'X') {
                std::cout << "No es tu ficha.\n";
                continue;
            }

            if (!puedeMoverFicha(tablero, f1, c1)) {
                std::cout << "La ficha no puede moverse. Escoge otra.\n";
                continue;
            }

            std::cout << "¿Hacia qué lado la quieres mover?: ";
            std::cin >> destino;

            if (destino.size() != 2) {
                std::cout << "Formato incorrecto.\n";
                continue;
            }

            int c2 = destino[0] - 'a';
            int f2 = destino[1] - '1';

            if (f2 < 0 || f2 > 7 || c2 < 0 || c2 > 7) {
                std::cout << "Coordenada fuera del tablero.\n";
                continue;
            }

            int df = f2 - f1;
            int dc = c2 - c1;

            if (abs(df) == 1 && abs(dc) == 1 && tablero[f2][c2] == ' ') {
                tablero[f2][c2] = tablero[f1][c1];
                tablero[f1][c1] = ' ';
            } 
            else if (abs(df) == 2 && abs(dc) == 2) {
                int fMedio = (f1 + f2) / 2;
                int cMedio = (c1 + c2) / 2;

                if (tablero[fMedio][cMedio] == 'O' && tablero[f2][c2] == ' ') {
                    tablero[f2][c2] = 'X';
                    tablero[f1][c1] = ' ';
                    tablero[fMedio][cMedio] = ' ';

                    f1 = f2;
                    c1 = c2;
                    while (true) {
                        bool puedeSeguir = false;
                        int movimientos[] = {-2, 2};
                        for (int i = 0; i < 2; i++) {
                            for (int j = 0; j < 2; j++) {
                                int nf = f1 + movimientos[i];
                                int nc = c1 + movimientos[j];
                                int fMed = (f1 + nf) / 2;
                                int cMed = (c1 + nc) / 2;
                                if (nf >= 0 && nf < 8 && nc >= 0 && nc < 8 &&
                                    tablero[nf][nc] == ' ' &&
                                    tablero[fMed][cMed] == 'O') {
                                    puedeSeguir = true;
                                }
                            }
                        }
                        if (!puedeSeguir) break;

                        mostrarTablero(tablero);
                        std::cout << "Sigues comiendo con la misma ficha.\n";
                        std::cout << "Elige dirección: ";
                        std::cin >> destino;
                        if (destino.size() != 2) break;
                        c2 = destino[0] - 'a';
                        f2 = destino[1] - '1';
                        int df3 = f2 - f1;
                        int dc3 = c2 - c1;
                        if (abs(df3) == 2 && abs(dc3) == 2) {
                            int fMed = (f1 + f2) / 2;
                            int cMed = (c1 + c2) / 2;
                            if (tablero[fMed][cMed] == 'O' && tablero[f2][c2] == ' ') {
                                tablero[f2][c2] = 'X';
                                tablero[f1][c1] = ' ';
                                tablero[fMed][cMed] = ' ';
                                f1 = f2;
                                c1 = c2;
                            } else break;
                        } else break;
                    }
                } else {
                    std::cout << "Movimiento incorrecto.\n";
                    continue;
                }
            } else {
                std::cout << "Movimiento incorrecto.\n";
                continue;
            }
        } 
        else {
            if (contraIA) {
                std::cout << "\nTurno de la computadora (O)\n";
                movimientoIA(tablero);
            } else {
                std::cout << "\nLe toca al jugador 2 (O)\n";

                std::string origen, destino;
                std::cout << "Qué ficha quieres mover: ";
                std::cin >> origen;

                if (origen.size() != 2) {
                    std::cout << "Formato incorrecto.\n";
                    continue;
                }

                int c1 = origen[0] - 'a';
                int f1 = origen[1] - '1';

                if (f1 < 0 || f1 > 7 || c1 < 0 || c1 > 7) {
                    std::cout << "Coordenada fuera del tablero.\n";
                    continue;
                }

                if (tablero[f1][c1] != 'O') {
                    std::cout << "No es tu ficha.\n";
                    continue;
                }

                if (!puedeMoverFicha(tablero, f1, c1)) {
                    std::cout << "La ficha no puede moverse. Escoge otra.\n";
                    continue;
                }

                std::cout << "¿Hacia qué lado la quieres mover?: ";
                std::cin >> destino;

                if (destino.size() != 2) {
                    std::cout << "Formato incorrecto.\n";
                    continue;
                }

                int c2 = destino[0] - 'a';
                int f2 = destino[1] - '1';

                if (f2 < 0 || f2 > 7 || c2 < 0 || c2 > 7) {
                    std::cout << "Coordenada fuera del tablero.\n";
                    continue;
                }

                tablero[f2][c2] = tablero[f1][c1];
                tablero[f1][c1] = ' ';
            }
        }

        turnoJugador1 = !turnoJugador1;
    }

    std::cout << "\nFin de la partida. ¡Gracias por jugar!\n";
}
