#include "../../headers/zwierzeta/Cyberowca.hpp"
#include "../../headers/parametry.hpp"

Cyberowca::Cyberowca(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::CYBEROWCA, koordynaty, swiat) {
    this->sila = SILA_CYBEROWCA;
    this->inicjatywa = INICJATYWA_CYBEROWCA;
};

char Cyberowca::GetSymbol() {
    return 'C';
};