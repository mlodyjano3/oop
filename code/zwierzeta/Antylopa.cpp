#include "../../headers/zwierzeta/Antylopa.hpp"
#include "../../headers/parametry.hpp"
#include "../../headers/Swiat.hpp"
#include <vector>
#include <cstdlib>

Antylopa::Antylopa(Koordynaty koordynaty, Swiat* swiat)
    : Zwierze(TypZwierzecia::ANTYLOPA, koordynaty, swiat) {
    this->sila = SILA_ANTYLOPA;
    this->inicjatywa = INICJATYWA_ANTYLOPA;
}

// zasieg dwukrotny
void Antylopa::akcja() {
    poprzednieKoordynaty = this->koordynaty;
    Koordynaty stare = this->koordynaty;

    std::vector<Koordynaty> mozliwosci;
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (dx == 0 && dy == 0) continue;
            Koordynaty k = {stare.x + dx, stare.y + dy};
            if (swiat->czyNaMapie(k)) mozliwosci.push_back(k);
        }
    }
    if (mozliwosci.empty()) return;

    Koordynaty cel = mozliwosci[rand() % mozliwosci.size()];
    if (swiat->czyWolne(cel)) {
        swiat->zmienKoordynatyOrganizmu(this, cel);
    } else {
        Organizm* kolidujacy = swiat->getOrganizmAt(cel);
        if (kolidujacy != nullptr) this->kolizja(kolidujacy);
    }
}

bool Antylopa::czyUciekl(Organizm* atakujacy) {
    if (rand() % 2 != 0) {
        return false;
    }; // 50% szans

    Koordynaty stare = this->koordynaty;
    Koordynaty sasiedzi[8] = {
        {stare.x-1,stare.y-1},{stare.x-1,stare.y},{stare.x-1,stare.y+1},
        {stare.x,stare.y-1},  {stare.x,stare.y+1},
        {stare.x+1,stare.y-1},{stare.x+1,stare.y},{stare.x+1,stare.y+1}
    };
    std::vector<Koordynaty> wolne;
    for (int i =0; i < 8; i++) {
        if (swiat->czyNaMapie(sasiedzi[i]) && swiat->czyWolne(sasiedzi[i]))
            wolne.push_back(sasiedzi[i]);
    };


    if (!wolne.empty()) {
        swiat->zmienKoordynatyOrganizmu(this, wolne[rand() % wolne.size()]);
        swiat->dodajKomunikat("Antylopa uciekla przed " +
            std::string(1, atakujacy->GetSymbol()) + "!");
        return true;
    };


    return false; // nie ma wolnego pola — walka nieunikniona
}

Organizm* Antylopa::stworzPotomka(Koordynaty k) {
    return new Antylopa(k, swiat);
}

char Antylopa::GetSymbol() { return 'A'; }