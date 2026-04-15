#include "../../headers/zwierzeta/Antylopa.hpp"
#include "../../headers/parametry.hpp"

Antylopa::Antylopa(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::ANTYLOPA, koordynaty, swiat) {
    this->sila = SILA_ANTYLOPA;
    this->inicjatywa = INICJATYWA_ANTYLOPA;
};

char Antylopa::GetSymbol() {
    return 'A';
};