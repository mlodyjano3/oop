#include "../../headers/zwierzeta/Lis.hpp"
#include "../../headers/parametry.hpp"
#include "../../headers/Swiat.hpp"
#include <vector>
#include <cstdlib>



Lis::Lis(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::LIS, koordynaty, swiat) {
    this->sila = SILA_LIS;
    this->inicjatywa = INICJATYWA_LIS;
};

void Lis::akcja() {
    poprzednieKoordynaty = this->koordynaty;
    Koordynaty stare = this->koordynaty;

    Koordynaty mozliwosci[8] = {
        {stare.x-1,stare.y-1},{stare.x-1,stare.y},{stare.x-1,stare.y+1},
        {stare.x,stare.y-1},{stare.x,stare.y+1},
        {stare.x+1,stare.y-1},{stare.x+1,stare.y},{stare.x+1,stare.y+1}
    };

    std::vector<Koordynaty> bezpieczne;
    for (int i = 0; i < 8; i++) {
        if (!swiat->czyNaMapie(mozliwosci[i])) continue;
        Organizm* org = swiat->getOrganizmAt(mozliwosci[i]);
        if (org == nullptr || org->getSila() <= this->getSila()) {
            bezpieczne.push_back(mozliwosci[i]);
        }
    }

    if (bezpieczne.empty()) return;
    Koordynaty cel = bezpieczne[rand() % bezpieczne.size()];

    if (swiat->czyWolne(cel)) {
        swiat->zmienKoordynatyOrganizmu(this, cel);
    } else {
        Organizm* kolidujacy = swiat->getOrganizmAt(cel);
        if (kolidujacy != nullptr) this->kolizja(kolidujacy);
    }
}

char Lis::GetSymbol() {
    return 'L';
}