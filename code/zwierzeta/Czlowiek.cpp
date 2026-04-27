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

char Czlowiek::GetSymbol() { return '&'; }
Kierunek Czlowiek::getKierunek() const { return kierunekRuchu; }

void Czlowiek::ustawKierunek(char znak) {
    kierunekRuchu = {0, 0};
    switch (znak) {
        case 'w': case 'W': kierunekRuchu.dy = -1; break;
        case 's': case 'S': kierunekRuchu.dy =  1; break;
        case 'a': case 'A': kierunekRuchu.dx = -1; break;
        case 'd': case 'D': kierunekRuchu.dx =  1; break;
        default: break;
    }
}

void Czlowiek::aktywujUmiejetnosc() {
    if (turyOdnowienia > 0) {
        swiat->dodajKomunikat("Tarcza Alzura: cooldown jeszcze " + std::to_string(turyOdnowienia) + " tur");
        return;
    }
    umiejetnoscAktywna = true;
    turyAktywnosci = 5;
    swiat->dodajKomunikat("Tarcza Alzura AKTYWOWANA na 5 tur!");
}

void Czlowiek::kolizja(Organizm* atakujacy) {
    if (umiejetnoscAktywna) {
        Koordynaty stare = atakujacy->getKoordynaty();
        Koordynaty sasiedzi[8] = {
            {stare.x-1,stare.y-1},{stare.x-1,stare.y},{stare.x-1,stare.y+1},
            {stare.x,stare.y-1},{stare.x,stare.y+1},
            {stare.x+1,stare.y-1},{stare.x+1,stare.y},{stare.x+1,stare.y+1}
        };
        std::vector<Koordynaty> wolne;
        for (int i = 0; i < 8; i++) {
            if (swiat->czyNaMapie(sasiedzi[i]) && swiat->czyWolne(sasiedzi[i]))
                wolne.push_back(sasiedzi[i]);
        }
        if (!wolne.empty()) {
            swiat->zmienKoordynatyOrganizmu(atakujacy, wolne[rand() % wolne.size()]);
            swiat->dodajKomunikat("Tarcza Alzura odephnela " + std::string(1, atakujacy->GetSymbol()) + "!");
        }
        return; // bez walki
    }
    Zwierze::kolizja(atakujacy);
}

void Czlowiek::akcja() {
    Koordynaty noweKoordynaty = {
        this->koordynaty.x + kierunekRuchu.dx,
        this->koordynaty.y + kierunekRuchu.dy
    };
    kierunekRuchu = {0, 0}; // reset PRZED ruchem

    if (noweKoordynaty.x != this->koordynaty.x || noweKoordynaty.y != this->koordynaty.y) {
        if (swiat->czyNaMapie(noweKoordynaty)) {
            if (swiat->czyWolne(noweKoordynaty)) {
                swiat->zmienKoordynatyOrganizmu(this, noweKoordynaty);
            } else {
                Organizm* kolidujacy = swiat->getOrganizmAt(noweKoordynaty);
                if (kolidujacy != nullptr) this->kolizja(kolidujacy);
            }
        }
    }

    // odliczanie - działa też gdy stoi w miejscu
    if (umiejetnoscAktywna) {
        turyAktywnosci--;
        if (turyAktywnosci == 0) {
            umiejetnoscAktywna = false;
            turyOdnowienia = 5;
            swiat->dodajKomunikat("Tarcza Alzura dezaktywowana. Cooldown: 5 tur.");
        }
    } else if (turyOdnowienia > 0) {
        turyOdnowienia--;
    }
}