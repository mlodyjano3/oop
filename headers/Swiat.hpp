#ifndef SWIAT_HPP
#define SWIAT_HPP

#include <vector>
#include "structures.hpp"
#include <string>
#include <iostream>
#include "Organizm.hpp"
#include "./zwierzeta/Czlowiek.hpp"

class Organizm;

class Swiat {
    private:
        Wymiary wymiary;

        std::vector<Organizm*> organizmy;
        std::vector<std::vector<Organizm*>> plansza;
        std::vector<std::string> komunikaty;

        Czlowiek *czlowiek;
    public:
        Swiat(int dlugosc, int wysokosc);

        int getDlugosc() const;
        int getWysokosc() const;

        void dodajOrganizm(Organizm* organizm);
        void usunOrganizm(Organizm* organizm);
        bool porownajOrganizmy(Organizm* a, Organizm* b);
        bool zmienKoordynatyOrganizmu(Organizm* organizm, Koordynaty noweKoordynaty);

        Organizm* getOrganizmAt(Koordynaty koordynaty);

        bool czyWolne(Koordynaty koordynaty);
        bool czyNaMapie(Koordynaty koordynaty);

        void wezInputUzytkownika();
        void wykonajTure();
        void rysujSwiat();

        void rysujPoziomaLinie();
        void rysujTekst(std::string tekst);
        void rysujInterfejs();
        void rysujKomunikaty();

        void dodajKomunikat(TypKomunikatu typ);

        ~Swiat();
};

#endif