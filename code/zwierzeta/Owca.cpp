#include "../../headers/zwierzeta/Owca.hpp"
#include "../../headers/parametry.hpp"

Owca::Owca(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::OWCA, koordynaty, swiat) {
    this->sila = SILA_OWCA;
    this->inicjatywa = INICJATYWA_OWCA;
};

Organizm* Owca::stworzPotomka(Koordynaty k) {
    return new Owca(k, swiat);
};

char Owca::GetSymbol() {
    return 'O';
}