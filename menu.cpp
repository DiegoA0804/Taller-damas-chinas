#include "menu.h"
#include "juego.h"
#include <iostream>


void mostrarMenu() {
    int opcion;
    do {
        std::cout << "::============================::\n";
        std::cout << "             DAMAS            \n";
        std::cout << "::==========================::\n";
        std::cout << "1. 1v1 2 jugadores\n";
        std::cout << "2. Jugador vs Computadora\n";
        std::cout << "3. Salir\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                jugar(false); 
                break;
            case 2:
                jugar(true); 
                break;
            case 3:
                std::cout << "Saliendo del juego...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 3);
}