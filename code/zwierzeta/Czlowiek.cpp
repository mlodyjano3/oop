#include "../../headers/zwierzeta/Czlowiek.hpp"
#include "../../headers/parametry.hpp"
#include "../../headers/Swiat.hpp"
#include <vector>
#include <cstdlib>

Czlowiek::Czlowiek(Koordynaty koordynaty, Swiat* swiat)
    : Zwierze(TypZwierzecia::CZLOWIEK, koordynaty, swiat) {
    this->sila = SILA_CZLOWIEK;
    this->inicjatywa = INICJATYWA_CZLOWIEK;
    kierunekRuchu = {0, 0};
}

char Czlowiek::GetSymbol() {
    return '&';
}

Kierunek Czlowiek::getKierunek() const {
    return kierunekRuchu;
}

void Czlowiek::ustawKierunek(char znak) {
    kierunekRuchu = {0, 0};
    switch (znak) {
        case 'w': case 'W': {
            kierunekRuchu.dy = -1; 
        };
        break;
        case 's': case 'S':{
            kierunekRuchu.dy =1; 
            break;
        };
        case 'a': case 'A':{
            kierunekRuchu.dx = -1; 
            break;
        };
        case 'd': case 'D':{ 
            kierunekRuchu.dx =1; 
            break;
        };
        default:{
            break;
        }; 
    }
}

void Czlowiek::aktywujUmiejetnosc() {
    if (turyOdnowienia > 0) {
        swiat->dodajKomunikat("Tarcza: cooldown jeszcze " +
            std::to_string(turyOdnowienia) + " tur");
        return;
    }
    umiejetnoscAktywna = true;
    turyAktywnosci = 5;
    swiat->dodajKomunikat("Tarcza Alzura AKTYWOWANA na 5 tur!");
};


bool Czlowiek::czyOdbilAtak(Organizm* atakujacy) {
    if (!umiejetnoscAktywna) return false;

    Koordynaty stare = atakujacy->getKoordynaty();
    Koordynaty sasiedzi[8] = {
        {stare.x-1,stare.y-1},{stare.x-1,stare.y},{stare.x-1,stare.y+1},
        {stare.x,stare.y-1},  {stare.x,stare.y+1},
        {stare.x+1,stare.y-1},{stare.x+1,stare.y},{stare.x+1,stare.y+1}
    };
    std::vector<Koordynaty> wolne;
    for (int i = 0; i < 8; i++) {
        if (swiat->czyNaMapie(sasiedzi[i]) && swiat->czyWolne(sasiedzi[i]))
            wolne.push_back(sasiedzi[i]);
    }
    if (!wolne.empty()) {
        swiat->zmienKoordynatyOrganizmu(atakujacy, wolne[rand() % wolne.size()]);
        swiat->dodajKomunikat("Tarcza Alzura odpchela " + std::string(1, atakujacy->GetSymbol()) + "!");
    }
    return true; // zawsze odbija gdy tarcza aktywna
};

void Czlowiek::akcja() {
    Koordynaty nowe = {
        this->koordynaty.x + kierunekRuchu.dx,
        this->koordynaty.y + kierunekRuchu.dy
    };
    kierunekRuchu = {0, 0}; // reset kierunku

    if (nowe.x != this->koordynaty.x || nowe.y != this->koordynaty.y) {
        if (swiat->czyNaMapie(nowe)) {
            if (swiat->czyWolne(nowe)) {
                swiat->zmienKoordynatyOrganizmu(this, nowe);
            } else {
                Organizm* kolidujacy = swiat->getOrganizmAt(nowe);
                if (kolidujacy != nullptr) this->kolizja(kolidujacy);
            };
        };
    };

    // odliczanie tarczy — dziala tez gdy czlowiek stoi w miejscu
    if (umiejetnoscAktywna) {
        turyAktywnosci--;
        if (turyAktywnosci == 0) {
            umiejetnoscAktywna = false;
            turyOdnowienia = 5;
            swiat->dodajKomunikat("Tarcza Alzura wygasla. Cooldown: 5 tur.");
        };
    } else if (turyOdnowienia > 0) {
        turyOdnowienia--;
    };
};