#include "../../headers/zwierzeta/Lis.hpp"
#include "../../headers/parametry.hpp"

Lis::Lis(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::LIS, koordynaty, swiat) {
    this->sila = SILA_LIS;
    this->inicjatywa = INICJATYWA_LIS;
};

char Lis::GetSymbol() {
    return 'L';
}