#include "menu.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned) time(nullptr)); // inicializa la RNG
    mostrarMenu();
    return 0;
}
