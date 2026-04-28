#include "../../headers/zwierzeta/Wilk.hpp"
#include "../../headers/parametry.hpp"

Wilk::Wilk(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::WILK, koordynaty, swiat) {
    this->sila = SILA_WILK;
    this->inicjatywa = INICJATYWA_WILK;
};

Organizm* Wilk::stworzPotomka(Koordynaty k) {
    return new Wilk(k, swiat);
};

char Wilk::GetSymbol() {
    return 'W';
}