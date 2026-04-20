#include <ctime>
#include "Swiat.hpp"
#include "Zwierze.hpp"
#include "../headers/parametry.hpp"

int main() {
    srand(time(NULL));

    // init swiata
    Swiat swiat(SZEROKOSC_PLANSZY, WYSOKOSC_PLANSZY);

    swiat.rysujInterfejs();

    while (true ) {
        
        swiat.wezInputUzytkownika();
        swiat.wykonajTure();
        swiat.rysujInterfejs();
   
    }
    return 0;
};