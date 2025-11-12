#include "ia.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

bool puedeMoverFichaIA(char tablero[8][8], int f, int c) {
    if (tablero[f][c] != 'O') return false;

    int direcciones[2][2] = {{-1, 1}, {-1, -1}};
    for (int i = 0; i < 2; i++) {
        int nf = f + direcciones[i][0];
        int nc = c + direcciones[i][1];
        int cf = f + 2 * direcciones[i][0];
        int cc = c + 2 * direcciones[i][1];

        // Movimiento simple
        if (nf >= 0 && nf < 8 && nc >= 0 && nc < 8 && tablero[nf][nc] == ' ')
            return true;

        // Movimiento de captura
        if (cf >= 0 && cf < 8 && cc >= 0 && cc < 8 &&
            tablero[nf][nc] != ' ' && tablero[cf][cc] == ' ') {
            if (tablero[nf][nc] == 'X')
                return true;
        }
    }
    return false;
}

void movimientoIA(char tablero[8][8]) {
    std::srand(std::time(0));
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> posibles;
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            if (tablero[f][c] == 'O' && puedeMoverFichaIA(tablero, f, c)) {
                int df_values[2] = {-2, 2};
                int dc_values[2] = {-2, 2};
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        int df = df_values[i];
                        int dc = dc_values[j];
                        int nf = f + df;
                        int nc = c + dc;
                        int fMed = (f + nf) / 2;
                        int cMed = (c + nc) / 2;
                        if (nf >= 0 && nf < 8 && nc >= 0 && nc < 8 &&
                            tablero[nf][nc] == ' ' &&
                            tablero[fMed][cMed] == 'X') {
                            posibles.push_back({{f, c}, {nf, nc}});
                        }
                    }
                }
                int df_values2[2] = {-1, 1};
                int dc_values2[2] = {-1, 1};
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        int df = df_values2[i];
                        int dc = dc_values2[j];
                        int nf = f + df;
                        int nc = c + dc;
                        if (nf >= 0 && nf < 8 && nc >= 0 && nc < 8 &&
                            tablero[nf][nc] == ' ') {
                            posibles.push_back({{f, c}, {nf, nc}});
                        }
                    }
                }
            }
        }
    }

    if (posibles.empty()) {
        std::cout << "La computadora no tiene movimientos disponibles.\n";
        return;
    }

    auto mov = posibles[std::rand() % posibles.size()];
    int f1 = mov.first.first, c1 = mov.first.second;
    int f2 = mov.second.first, c2 = mov.second.second;

    int df = f2 - f1;
    int dc = c2 - c1;

    if (std::abs(df) == 2 && std::abs(dc) == 2) {
        int fMed = (f1 + f2) / 2;
        int cMed = (c1 + c2) / 2;
        tablero[fMed][cMed] = ' ';
    }

    tablero[f2][c2] = tablero[f1][c1];
    tablero[f1][c1] = ' ';

    std::cout << "La computadora movió de (" << f1 + 1 << "," << char('a' + c1)
              << ") a (" << f2 + 1 << "," << char('a' + c2) << ").\n";

    f1 = f2;
    c1 = c2;
    while (true) {
        bool puedeSeguir = false;
        int nf, nc, fMed, cMed;
        int df2_values[2] = {-2, 2};
        int dc2_values[2] = {-2, 2};

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int df2 = df2_values[i];
                int dc2 = dc2_values[j];
                nf = f1 + df2;
                nc = c1 + dc2;
                fMed = (f1 + nf) / 2;
                cMed = (c1 + nc) / 2;
                if (nf >= 0 && nf < 8 && nc >= 0 && nc < 8 &&
                    tablero[nf][nc] == ' ' &&
                    tablero[fMed][cMed] == 'X') {
                    puedeSeguir = true;
                    break;
                }
            }
            if (puedeSeguir) break;
        }

        if (!puedeSeguir) break;

        tablero[fMed][cMed] = ' ';
        tablero[nf][nc] = 'O';
        tablero[f1][c1] = ' ';
        f1 = nf;
        c1 = nc;

        std::cout << "La computadora realizó una captura encadenada.\n";
    }
}
