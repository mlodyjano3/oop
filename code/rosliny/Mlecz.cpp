#include "../../headers/rosliny/Mlecz.hpp"
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"
#include <cstdlib>

Mlecz::Mlecz(Koordynaty k, Swiat* s) : Roslina(ROSLINA, k, SILA_MLECZ, 0, s) {}
char Mlecz::GetSymbol() { return 'M'; }

void Mlecz::akcja() { rozrost(); rozrost(); rozrost(); }

void Mlecz::rozrost() {
    if (rand() % 5 != 0) return;
    Koordynaty cel = this->wybierzNoweKoordynaty();
    if (cel.x == koordynaty.x && cel.y == koordynaty.y) return;
    if (!swiat->czyWolne(cel)) return;
    swiat->dodajOrganizm(new Mlecz(cel, swiat));
}