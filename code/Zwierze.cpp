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
    Swiat* sw = swiat;

    if (this->GetSymbol() == kolidujacy->GetSymbol()) {
        if (this->wiek == 0 || kolidujacy->getWiek() == 0) return;
        Koordynaty kNoworodka = this->wybierzNoweKoordynatyNoworodka(this, kolidujacy);
        if (kNoworodka.x == -1 && kNoworodka.y == -1) return;
        Organizm* noworodek = this->stworzPotomka(kNoworodka);
        if (noworodek != nullptr) {
            sw->dodajOrganizm(noworodek);
            sw->dodajKomunikat("Narodziny: " + std::string(1, this->GetSymbol()) +
                " na (" + std::to_string(kNoworodka.x) + "," +
                std::to_string(kNoworodka.y) + ")");
        }
        return;
    }

    if (kolidujacy->czyOdbilAtak(this)) return;
    if (kolidujacy->czyUciekl(this)) return;

    if (kolidujacy->getTypOrganizmu() == ROSLINA) {
        Koordynaty celPola = kolidujacy->getKoordynaty();
        Koordynaty mojePole = this->getKoordynaty();

        kolidujacy->kolizja(this);

        Organizm* survivor = sw->getOrganizmAt(mojePole);
        if (survivor != nullptr) {
            sw->zmienKoordynatyOrganizmu(survivor, celPola);
        }
        return;
    }

    if (this->getSila() >= kolidujacy->getSila()) {
        Koordynaty celPola = kolidujacy->getKoordynaty();
        
        char symbolZwyciezcy = this->GetSymbol();
        char symbolPokonanego = kolidujacy->GetSymbol();

        sw->usunOrganizm(kolidujacy);
        sw->zmienKoordynatyOrganizmu(this, celPola);
        
        sw->dodajKomunikat(std::string(1, symbolZwyciezcy) + " pokonat " +
            std::string(1, symbolPokonanego));
    } else {
        char symbolZwyciezcy = kolidujacy->GetSymbol();
        char symbolPokonanego = this->GetSymbol();
        
        sw->usunOrganizm(this);
        
        sw->dodajKomunikat(std::string(1, symbolZwyciezcy) + " pokonat " +
            std::string(1, symbolPokonanego));
    };
}

void Zwierze::akcja() {
    poprzednieKoordynaty = this->koordynaty;

    Koordynaty noweKoordynaty = this->wybierzNoweKoordynaty();
    if (noweKoordynaty.x == this->koordynaty.x &&
        noweKoordynaty.y == this->koordynaty.y) return;

    if (swiat->czyWolne(noweKoordynaty)) {
        swiat->zmienKoordynatyOrganizmu(this, noweKoordynaty);
    } else {
        Organizm* kolidujacy = swiat->getOrganizmAt(noweKoordynaty);
        if (kolidujacy == nullptr) {return;};

        this->kolizja(kolidujacy);
    };
};;
