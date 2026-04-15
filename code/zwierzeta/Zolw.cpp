#include "../../headers/zwierzeta/Zolw.hpp"
#include "../../headers/parametry.hpp"

Zolw::Zolw(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::ZOLW, koordynaty, swiat) {
    this->sila = SILA_ZOLW;
    this->inicjatywa = INICJATYWA_ZOLW;
};

char Zolw::GetSymbol() {
    return 'Z';
}