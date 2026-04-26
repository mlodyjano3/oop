#include "../../headers/rosliny/WilczeJagody.hpp"
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"
#include <cstdlib>

WilczeJagody::WilczeJagody(Koordynaty k, Swiat* s) : Roslina(ROSLINA, k, SILA_WILCZE_JAGODY, 0, s) {}
char WilczeJagody::GetSymbol() { return 'J'; }

void WilczeJagody::rozrost() {
    if (rand() % 5 != 0) return;
    Koordynaty cel = this->wybierzNoweKoordynaty();
    if (cel.x == koordynaty.x && cel.y == koordynaty.y) return;
    if (!swiat->czyWolne(cel)) return;
    swiat->dodajOrganizm(new WilczeJagody(cel, swiat));
}

void WilczeJagody::kolizja(Organizm* atakujacy) {
    swiat->dodajKomunikat("Wilcze jagody: " + std::string(1, atakujacy->GetSymbol()) + " zginal!");
    swiat->usunOrganizm(atakujacy);
    swiat->usunOrganizm(this);
}