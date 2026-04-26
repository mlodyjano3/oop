#include "../../headers/zwierzeta/Czlowiek.hpp"
#include "../../headers/parametry.hpp"
#include "../../headers/Swiat.hpp"

Czlowiek::Czlowiek(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::CZLOWIEK, koordynaty, swiat) {
    this->sila = SILA_CZLOWIEK;
    this->inicjatywa = INICJATYWA_CZLOWIEK;
};


void Czlowiek::ustawKierunek(char znak) {
    kierunekRuchu.dx = 0;
    kierunekRuchu.dy = 0;

    switch (znak) {
        case 72:
        case 'w':
        case 'W':
            kierunekRuchu.dy = -1;
            break;
        case 80:
        case 's':
        case 'S':
            kierunekRuchu.dy = 1;
            break;
        case 75:
        case 'a':
        case 'A':
            kierunekRuchu.dx = -1;
            break;
        case 77:
        case 'd':
        case 'D':
            kierunekRuchu.dx = 1;
            break;
        default:
            break;
    };
};

void Czlowiek::akcja() {
    Koordynaty noweKoordynaty = {
        this->koordynaty.x + kierunekRuchu.dx,
        this->koordynaty.y + kierunekRuchu.dy
    };

    if (
        noweKoordynaty.x == this->koordynaty.x 
        && noweKoordynaty.y == this->koordynaty.y) {
        return; 
    };

    kierunekRuchu.dx = 0;
    kierunekRuchu.dy = 0;

    if (swiat->czyNaMapie(noweKoordynaty)) {
        bool czyWolne = swiat->czyWolne(noweKoordynaty);

        if (czyWolne) {

            swiat->zmienKoordynatyOrganizmu(this, noweKoordynaty);
            this->koordynaty = noweKoordynaty;

        } else {

            Organizm* kolidujacy = swiat->getOrganizmAt(noweKoordynaty);
            
            if (kolidujacy != nullptr) {
                this->kolizja(kolidujacy);
            };
        };
    };
};

Kierunek Czlowiek::getKierunek() const {
    return kierunekRuchu;
};


char Czlowiek::GetSymbol() {
    return '&';
};