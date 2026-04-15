#include <ctime>
#include "Swiat.hpp"
#include "Zwierze.hpp"
#include "../headers/parametry.hpp"

int main() {
    srand(time(NULL));

    // init swiata
    Swiat swiat(SZEROKOSC_PLANSZY, WYSOKOSC_PLANSZY);

    while (true ) {
        
        swiat.wezInputUzytkownika();
        swiat.wykonajTure();
        swiat.rysujSwiat();

        

        
    }
    return 0;
};