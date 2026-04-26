#include "../../headers/rosliny/Trawa.hpp"
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"
#include <cstdlib>

Trawa::Trawa(Koordynaty k, Swiat* s) : Roslina(ROSLINA, k, SILA_TRAWA, 0, s) {}
char Trawa::GetSymbol() { return 'T'; }

void Trawa::rozrost() {
    if (rand() % 5 != 0) return;
    Koordynaty cel = this->wybierzNoweKoordynaty();
    if (cel.x == koordynaty.x && cel.y == koordynaty.y) return;
    if (!swiat->czyWolne(cel)) return;
    swiat->dodajOrganizm(new Trawa(cel, swiat));
}