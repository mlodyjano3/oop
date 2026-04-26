#include "../../headers/zwierzeta/Zolw.hpp"
#include <cstdlib>
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"

Zolw::Zolw(Koordynaty koordynaty, Swiat* swiat) : Zwierze(TypZwierzecia::ZOLW, koordynaty, swiat) {
    this->sila = SILA_ZOLW;
    this->inicjatywa = INICJATYWA_ZOLW;
};

void Zolw::akcja() {
    if (rand() % 4 != 0) return; // 75% szans na bezru
    poprzednieKoordynaty = this->koordynaty;
    Zwierze::akcja();
};

void Zolw::kolizja(Organizm* atakujacy) {
    if (atakujacy->getSila() < 5) {
        Zwierze* zwAtakujacy = dynamic_cast<Zwierze*>(atakujacy);
        if (zwAtakujacy != nullptr) {
            Koordynaty cofniecie = zwAtakujacy->getPoprzednieKoordynaty();
            if (swiat->czyNaMapie(cofniecie) && swiat->czyWolne(cofniecie)) {
                swiat->zmienKoordynatyOrganizmu(atakujacy, cofniecie);
            }
        }
        swiat->dodajKomunikat("Zolw odparl atak!");
    } else {
        Zwierze::kolizja(atakujacy);
    }
}

char Zolw::GetSymbol() {
    return 'Z';
}