#include "Zwierze.hpp"



Zwierze::Zwierze(TypZwierzecia typ, Koordynaty koordynaty, Swiat* swiat) {
    this->typOrganizmu = ZWIERZE;

    this->typZwierzecia = typ;
    this->koordynaty = koordynaty;
    this->swiat = swiat;

    this->wiek = 0;
};

TypZwierzecia Zwierze::getTypZwierzecia() const {
    return this->typZwierzecia;
};

void Zwierze::kolizja(Organizm* kolidujacy) {


};

void Zwierze::akcja() {
    Koordynaty nowe_koordynaty = this->wybierzNoweKoordynaty();
    if (nowe_koordynaty.x == this->koordynaty.x && nowe_koordynaty.y == this->koordynaty.y) return;

    if (swiat->czyWolne(nowe_koordynaty)) {
        swiat->zmienKoordynatyOrganizmu(this, nowe_koordynaty);
        this->koordynaty = nowe_koordynaty;
    } else {

        Organizm* kolidujacy = swiat->getOrganizmAt(nowe_koordynaty);
        if (kolidujacy != nullptr) {
            this->kolizja(kolidujacy);
        };
    };
};