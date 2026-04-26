#include "../../headers/rosliny/Guarana.hpp"
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"
#include <cstdlib>

Guarana::Guarana(Koordynaty k, Swiat* s) : Roslina(ROSLINA, k, SILA_GUARANA, 0, s) {}
char Guarana::GetSymbol() { return 'G'; }

void Guarana::rozrost() {
    if (rand() % 5 != 0) return;
    Koordynaty cel = this->wybierzNoweKoordynaty();
    if (cel.x == koordynaty.x && cel.y == koordynaty.y) return;
    if (!swiat->czyWolne(cel)) return;
    swiat->dodajOrganizm(new Guarana(cel, swiat));
}

void Guarana::kolizja(Organizm* atakujacy) {
    atakujacy->setSila(atakujacy->getSila() + 3);
    swiat->dodajKomunikat("Guarana: " + std::string(1, atakujacy->GetSymbol()) + " zyskal +3 sily! Sila: " + std::to_string(atakujacy->getSila()));
    swiat->usunOrganizm(this);
}