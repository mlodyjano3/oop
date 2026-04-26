#include "../../headers/zwierzeta/Cyberowca.hpp"
#include "../../headers/parametry.hpp"
#include "../../headers/Swiat.hpp"
#include <climits>
#include <cstdlib>
#include <cmath>

Cyberowca::Cyberowca(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::CYBEROWCA, koordynaty, swiat) {
    this->sila = SILA_CYBEROWCA;
    this->inicjatywa = INICJATYWA_CYBEROWCA;
};

void Cyberowca::akcja() {
    poprzednieKoordynaty = this->koordynaty;

    Organizm* najblizszBarszcz = nullptr;
    int minDystans = INT_MAX;

    for (Organizm* org : swiat->getOrganizmy()) {
        if (org == nullptr || org->GetSymbol() != 'B') continue;
        int dystans = abs(org->getKoordynaty().x - koordynaty.x) 
                    + abs(org->getKoordynaty().y - koordynaty.y);
        if (dystans < minDystans) {
            minDystans = dystans;
            najblizszBarszcz = org;
        }
    }

    if (najblizszBarszcz == nullptr) {
        Zwierze::akcja();
        return;
    }

    int dx = 0, dy = 0;
    Koordynaty kb = najblizszBarszcz->getKoordynaty();
    if (kb.x > koordynaty.x) {
        dx = 1;   
    } else if (kb.x < koordynaty.x) {
        dx = -1;
    };
    if (kb.y > koordynaty.y) {
        dy = 1;
    } else if (kb.y < koordynaty.y) { 
        dy = -1;
    };

    Koordynaty cel = {koordynaty.x + dx, koordynaty.y + dy};
    if (!swiat->czyNaMapie(cel)) return;

    if (swiat->czyWolne(cel)) {
        swiat->zmienKoordynatyOrganizmu(this, cel);
    } else {
        Organizm* kolidujacy = swiat->getOrganizmAt(cel);
        if (kolidujacy != nullptr) this->kolizja(kolidujacy);
    }
}

char Cyberowca::GetSymbol() {
    return 'C';
};