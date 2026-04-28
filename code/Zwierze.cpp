#include "../headers/Zwierze.hpp"
#include "../headers/Swiat.hpp"
#include <string>

Zwierze::Zwierze(TypZwierzecia typ, Koordynaty koordynaty, Swiat* swiat) {
    this->typOrganizmu = ZWIERZE;
    this->typZwierzecia = typ;
    this->koordynaty = koordynaty;
    this->swiat = swiat;
    this->wiek = 0;
}

TypZwierzecia Zwierze::getTypZwierzecia() const {
    return this->typZwierzecia;
}

Koordynaty Zwierze::getPoprzednieKoordynaty() const {
    return this->poprzednieKoordynaty;
}


void Zwierze::kolizja(Organizm* kolidujacy) {

    if (this->GetSymbol() == kolidujacy->GetSymbol()) {
        // oboje musza byc juz dorosli (wiek > 0), zeby noworodek nie rozmnazal sie w tej samej turze, w ktorej powstal
        if (this->wiek == 0 || kolidujacy->getWiek() == 0) return;

        Koordynaty kNoworodka = this->wybierzNoweKoordynatyNoworodka(this, kolidujacy);
        if (kNoworodka.x == -1 && kNoworodka.y == -1) return; // brak wolnego miejsca

        Organizm* noworodek = this->stworzPotomka(kNoworodka);
        if (noworodek != nullptr) {
            swiat->dodajOrganizm(noworodek);
            swiat->dodajKomunikat("Narodziny: " + std::string(1, this->GetSymbol()) + " na (" + std::to_string(kNoworodka.x) + "," +
                std::to_string(kNoworodka.y) + ")");
        }
        return;
    }

    if (kolidujacy->czyOdbilAtak(this)) {
        // kolidujacy sam obslugl ruch atakujacego w swojej metodzie
        return;
    }

    if (kolidujacy->czyUciekl(this)) {
        // kolidujacy sam sie przesunal w swojej metodzie
        return;
    }

    if (this->getSila() >= kolidujacy->getSila()) {
        Koordynaty celPola = kolidujacy->getKoordynaty();
        swiat->usunOrganizm(kolidujacy);
        swiat->zmienKoordynatyOrganizmu(this, celPola); // zajmij zwolnione pole
        swiat->dodajKomunikat(std::string(1, this->GetSymbol()) + " pokonat " +
            std::string(1, kolidujacy->GetSymbol()));
    } else {
        swiat->dodajKomunikat(std::string(1, kolidujacy->GetSymbol()) + " pokonat " +
            std::string(1, this->GetSymbol()));
        swiat->usunOrganizm(this);
    };
};

void Zwierze::akcja() {
    poprzednieKoordynaty = this->koordynaty; // zapamietaj przed ruchem

    Koordynaty noweKoordynaty = this->wybierzNoweKoordynaty();
    if (noweKoordynaty.x == this->koordynaty.x &&
        noweKoordynaty.y == this->koordynaty.y) return; // nie ma gdzie isc

    if (swiat->czyWolne(noweKoordynaty)) {
        swiat->zmienKoordynatyOrganizmu(this, noweKoordynaty);
    } else {
        Organizm* kolidujacy = swiat->getOrganizmAt(noweKoordynaty);
        if (kolidujacy != nullptr) {
            this->kolizja(kolidujacy);
        }
    }
}