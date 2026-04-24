#include "../headers/Zwierze.hpp"
#include "../headers/Swiat.hpp"

#include "../headers/zwierzeta/Wilk.hpp"
#include "../headers/zwierzeta/Owca.hpp"
#include "../headers/zwierzeta/Lis.hpp"
#include "../headers/zwierzeta/Zolw.hpp"
#include "../headers/zwierzeta/Antylopa.hpp"
#include "../headers/zwierzeta/Cyberowca.hpp"


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
    TypOrganizmu this_typ_organizmu = this->getTypOrganizmu();
    TypOrganizmu typ_kolidujacego = kolidujacy->getTypOrganizmu();

    // czy to ten sam gatunek 
    if (this->GetSymbol() == kolidujacy->GetSymbol()) {
        if (this->wiek > 0 && kolidujacy->getWiek() > 0) {
            // rozmnazanie
            Koordynaty koordynaty_noworodka = this->wybierzNoweKoordynatyNoworodka(this, kolidujacy);

            // zeby noworodek sie nie rozmnozyl od razu
            if (koordynaty_noworodka.x == -1 && koordynaty_noworodka.y == -1) {
                return;
            };

            Organizm* noworodek = nullptr;

            switch(this->getTypZwierzecia()) {
                case TypZwierzecia::WILK:
                    noworodek = new Wilk(koordynaty_noworodka, this->swiat);
                    break;
                case TypZwierzecia::OWCA:
                    noworodek = new Owca(koordynaty_noworodka, this->swiat);
                    break;
                case TypZwierzecia::LIS:
                    noworodek = new Lis(koordynaty_noworodka, this->swiat);
                    break;
                case TypZwierzecia::ZOLW:
                    noworodek = new Zolw(koordynaty_noworodka, this->swiat);
                    break;
                case TypZwierzecia::ANTYLOPA:
                    noworodek = new Antylopa(koordynaty_noworodka, this->swiat);
                    break;
                case TypZwierzecia::CYBEROWCA:
                    noworodek = new Cyberowca(koordynaty_noworodka, this->swiat);
                    break;
                default:
                    break;
            }

            if (noworodek != nullptr) {
                if (swiat->czyWolne(noworodek->getKoordynaty())) {
                    swiat->zmienKoordynatyOrganizmu(noworodek, koordynaty_noworodka);
                } else {
                    // usuwanie noworodka jezeli nie ma miejsac na niego 
                    delete noworodek;
                    return;
                }
                swiat->dodajOrganizm(noworodek);
                std::string komunikat = "Nowe zwierze: " + std::to_string(noworodek->getTypOrganizmu()) + " na koordynatach: (" + std::to_string(noworodek->getKoordynaty().x) + ", " + std::to_string(noworodek->getKoordynaty().y) + ")";
            };
            
            return;
        };
    } else {
        // walka
        int this_sila = this->getSila();
        int kolidujacy_sila = kolidujacy->getSila();
        
        if (this_sila >= kolidujacy_sila) {
            // wygrywa obiekt this
            // Koordynaty koordy_kolidujacego = kolidujacy->getKoordynaty();
            swiat->usunOrganizm(kolidujacy);
            // swiat->zmienKoordynatyOrganizmu(this, koordy_kolidujacego); 
        } else {
            // wygrywa obiekt kolidujacy
            // Koordynaty koordy_this = this->getKoordynaty();
            swiat->usunOrganizm(this);
            // swiat->zmienKoordynatyOrganizmu(kolidujacy, koordy_this);
        };
    };
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