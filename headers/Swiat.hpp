#ifndef SWIAT_HPP
#define SWIAT_HPP

#include <vector>
#include "structures.hpp"
#include <string>
#include <iostream>
#include "Organizm.hpp"
#include "Zwierze.hpp"
#include "parametry.hpp"

class Organizm;
class Zwierze;
class Czlowiek;

class Swiat {
    private:
        Wymiary wymiary;
        int tura;
        bool graSkonczona;
        std::string komunikatKonca;

        std::vector<Organizm*> organizmy;
        std::vector<std::vector<Organizm*>> plansza;
        std::vector<std::string> komunikaty;

        Czlowiek *czlowiek;

        Organizm* stworzOrganizm(char symbol, Koordynaty k);
        bool dodajOrganizmWewnetrznie(Organizm* organizm, bool ignorujLimity);
        void ustawRozmiarPlanszy(int dlugosc, int wysokosc);
        void wyczyscSwiat();
        void usunPusteWpisy();
        void inicjalizujDomyslneOrganizmy();
        Koordynaty znajdzLosoweWolnePole() const;
        Koordynaty znajdzNajblizszeWolnePoleOdSrodka() const;
        int getPojemnoscPlanszy() const;
        int getMaksLiczbaRoslin() const;
        int getMaksLiczbaZwierzat() const;
        int getSzerokoscOkna() const;
        bool czyMoznaDodacOrganizm(Organizm* organizm) const;
    public:
        Swiat(int dlugosc, int wysokosc, bool inicjalizujDomyslnie = true);

        const std::vector<Organizm*>& getOrganizmy() const;
        Czlowiek* getCzlowiek() const;

        int getDlugosc() const;
        int getWysokosc() const;
        int getTura() const;
        int getLiczbaOrganizmow() const;
        int getLiczbaRoslin() const;
        int getLiczbaZwierzat() const;
        bool czyGraSkonczona() const;
        const std::string& getKomunikatKonca() const;

        void dodajOrganizm(Organizm* organizm);
        void usunOrganizm(Organizm* organizm);
        bool porownajOrganizmy(Organizm* a, Organizm* b);
        bool zmienKoordynatyOrganizmu(Organizm* organizm, Koordynaty noweKoordynaty);

        Organizm* getOrganizmAt(Koordynaty koordynaty) const;

        bool czyWolne(Koordynaty koordynaty) const;
        bool czyNaMapie(Koordynaty koordynaty) const;

        void wezInputUzytkownika();
        void wykonajTure();
        void rysujSwiat();

        void rysujPoziomaLinie();
        void rysujTekst(std::string tekst);
        void rysujInterfejs();
        void rysujKomunikaty();

        void dodajKomunikat(TypKomunikatu typ);
        void dodajKomunikat(std::string tekst);



        void zapiszStanSwiata();
        void zapiszStanSwiata(const std::string& sciezka);
        bool wczytajStanSwiata();
        bool wczytajStanSwiata(const std::string& sciezka);

        ~Swiat();
};

#endif
