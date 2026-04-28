#include "../../headers/zwierzeta/Zolw.hpp"
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"
#include <cstdlib>

Zolw::Zolw(Koordynaty koordynaty, Swiat* swiat)
    : Zwierze(TypZwierzecia::ZOLW, koordynaty, swiat) {
    this->sila = SILA_ZOLW;
    this->inicjatywa = INICJATYWA_ZOLW;
}

// 75% szans na bezruch
void Zolw::akcja() {
    poprzednieKoordynaty = this->koordynaty;
    if (rand() % 4 != 0) return;
    Zwierze::akcja();
}

bool Zolw::czyOdbilAtak(Organizm* atakujacy) {
    if (atakujacy->getSila() < 5) {
        swiat->dodajKomunikat("Zolw odparl atak " +
            std::string(1, atakujacy->GetSymbol()) + "!");
        return true;
    }
    return false;
}

Organizm* Zolw::stworzPotomka(Koordynaty k) {
    return new Zolw(k, swiat);
}

char Zolw::GetSymbol() { return 'Z'; }