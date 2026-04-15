#include <iostream>
#include "../headers/structures.hpp"
#include "../headers/Swiat.hpp"
#include <algorithm>
#include "../headers/Organizm.hpp"
#include "../headers/parametry.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>

Swiat::Swiat(int dlugosc, int wysokosc) {
    this->wymiary.dlugosc = dlugosc;
    this->wymiary.wysokosc = wysokosc;

    plansza.resize(wymiary.wysokosc, std::vector<Organizm*>(wymiary.dlugosc, nullptr));

    this->czlowiek = new Czlowiek({wymiary.dlugosc / 2, wymiary.wysokosc / 2}, this);

    dodajOrganizm(this->czlowiek);

    dodajKomunikat(TypKomunikatu::InicjalizacjaSwiata);
};

int Swiat::getDlugosc() const { 
    return wymiary.dlugosc;
};
int Swiat::getWysokosc() const { 
    return wymiary.wysokosc;
};

void Swiat::dodajOrganizm(Organizm* organizm) {
    if (organizm == nullptr) return;

    Koordynaty koordynaty_organizmu = organizm->getKoordynaty();

    if (plansza[koordynaty_organizmu.y][koordynaty_organizmu.x] == nullptr) {
        plansza[koordynaty_organizmu.y][koordynaty_organizmu.x] = organizm;
        organizmy.push_back(organizm);
    };

    dodajKomunikat(TypKomunikatu::NowyOrganizm);
};


void Swiat::usunOrganizm(Organizm* organizm) {
    if (organizm == nullptr) return;

    Koordynaty koordynaty_organizmu = organizm->getKoordynaty();

    plansza[koordynaty_organizmu.y][koordynaty_organizmu.x] = nullptr;

    for (size_t i = 0; i < organizmy.size(); i++) {
        if (organizmy[i] == organizm) {
            organizmy[i] = nullptr; 
            break;
        }
    }

    delete organizm;

    dodajKomunikat(TypKomunikatu::UsunietoOrganizm);
};

bool Swiat::porownajOrganizmy(Organizm* a, Organizm* b) {
    if (a == nullptr) return false;
    if (b == nullptr) return true;

    if (a->getInicjatywa() != b->getInicjatywa()) {
        return a->getInicjatywa() > b->getInicjatywa();

    } else {
        return a->getWiek() > b->getWiek(); 

    };
};

bool Swiat::zmienKoordynatyOrganizmu(Organizm* organizm, Koordynaty noweKoordynaty) {
    if (czyWolne(noweKoordynaty)) {
        Koordynaty stareKoordynaty = organizm->getKoordynaty();

        plansza[stareKoordynaty.y][stareKoordynaty.x] = nullptr;
        plansza[noweKoordynaty.y][noweKoordynaty.x] = organizm;
        return true;
    }
    return false;
};


Organizm* Swiat::getOrganizmAt(Koordynaty koordynaty) {
    if (
        koordynaty.x >= 0 && koordynaty.x < wymiary.dlugosc &&
        koordynaty.y >= 0 && koordynaty.y < wymiary.wysokosc
    ) { return plansza[koordynaty.y][koordynaty.x]; } else {
        return nullptr;
    }
};

bool Swiat::czyWolne(Koordynaty koordynaty) {
    return plansza[koordynaty.y][koordynaty.x] == nullptr;
};


void Swiat::wezInputUzytkownika() {
    char znak;
    std::cout << "Podaj kierunek ruchu (w - gora, s - dol, a - lewo, d - prawo): ";
    std::cin >> znak;

    czlowiek->ustawKierunek(znak);
};




void Swiat::wykonajTure() {
    organizmy.erase(std::remove(organizmy.begin(), organizmy.end(), nullptr), organizmy.end());

    std::sort(organizmy.begin(), organizmy.end(), [](Organizm* a, Organizm* b) {
        if (a == nullptr) return false;
        if (b == nullptr) return true;
        
        if (a->getInicjatywa() != b->getInicjatywa()) {
            return a->getInicjatywa() > b->getInicjatywa();
        }
        return a->getWiek() > b->getWiek();
    });

    for (int i=0; i < organizmy.size();i++ ) {
        if (organizmy[i] != nullptr) { // zjedzony czy nie
            organizmy[i]->akcja();
            organizmy[i]->zwiekszWiek();
        };
    };

    dodajKomunikat(TypKomunikatu::WykonanieTury);
};

void Swiat::rysujPoziomaLinie() {
    for (int i = 0; i < SZEROKOSC_OKNA; i++) {
        std::cout << DEKORATOR_POZIOMY;
    };
    std::cout << std::endl;
};

void Swiat::rysujTekst(std::string text) {
    const int LEFT = SZEROKOSC_OKNA - text.length() - 2;
    std::cout << DEKORATOR_PIONOWY << " " << text;
    for (int i = 0; i < LEFT - 1; i++) {
        std::cout << " ";
    };
    std::cout << DEKORATOR_PIONOWY << std::endl;
};

void Swiat::rysujKomunikaty() {
    int wieksza_wartosc;
    if (komunikaty.size() > MAX_KOMUNIKATOW) {
        wieksza_wartosc = MAX_KOMUNIKATOW;
    } else {
        wieksza_wartosc = komunikaty.size();
    };

    for ( int i = wieksza_wartosc - 1; i >= 0 && i < MAX_KOMUNIKATOW && i < komunikaty.size(); i--) {
        rysujTekst(komunikaty[i]);
    };
};

void Swiat::rysujSwiat() {
    for (int y =0; y < wymiary.wysokosc; y++) {
        std::cout << DEKORATOR_PIONOWY;
        for (int x=0; x < wymiary.dlugosc; x++){
            std::cout << " " << (plansza[y][x] != nullptr ? plansza[y][x]->GetSymbol() : '.') << " ";
        };
        std::cout << DEKORATOR_PIONOWY << std::endl;    
    };
}

void Swiat::rysujInterfejs() {
    system("clear");

    rysujPoziomaLinie(); // poczatek oka

    rysujTekst("Autor: Jan Krol, Indeks: 208228");
    rysujTekst("Grupa: 7A, Projekt: Swiat w cpp");
    rysujTekst("Legenda:");
    rysujTekst("& - Czlowiek, . - Puste pole");
    rysujTekst("A - Antylopa, W - Wilk, O - Owca, L - Lis, Z - Zolw");
    rysujTekst("T - Trawa, M - Mlecz, G - Guarana");
    rysujTekst("J - Wilcze jagody, B - Barszcz");

    rysujPoziomaLinie(); // koniec legendy, poczatek interface

    rysujTekst("Tura: " + std::to_string(1));
    rysujTekst("Liczba organizmow: " + std::to_string(organizmy.size()));

    rysujPoziomaLinie(); // koniec interface, swiat

    rysujSwiat();

    rysujPoziomaLinie(); // czesc komunikatowa

    rysujKomunikaty();

    rysujPoziomaLinie(); // koniec okna

};

void Swiat::dodajKomunikat(TypKomunikatu typ) {
    /*
    char czas[11];
    time_t teraz = time(0);
    strftime(czas, sizeof(czas), "[%H:%M:%S] ", localtime(&teraz));
    */

    std::string tekst = "log: ";
    if (typ == TypKomunikatu::NowyOrganizm) {
        tekst += "Dodano organizm";
    } else if (typ == TypKomunikatu::UsunietoOrganizm) {
        tekst += "Usunieto organizm";
    } else if (typ == TypKomunikatu::Atak) {
        tekst += "Atak";
    } else if (typ == TypKomunikatu::Rozmnozenie) {
        tekst += "Rozmnozenie";
    } else if (typ == TypKomunikatu::Smierc) {
        tekst += "Smierc";
    } else if (typ == TypKomunikatu::Blad) {
        tekst += "Blad";
    } else if (typ == TypKomunikatu::InicjalizacjaSwiata) {
        tekst += "Inicjalizacja swiata";
    } else if (typ == TypKomunikatu::ZmianaKoordynatowOrganizmu) {
        tekst += "Zmiana koordynatow organizmu";
    } else if (typ == TypKomunikatu::WykonanieTury) {
        tekst += "Wykonanie tury";
    } else {
        tekst += "Nieznany komunikat";
    };
    komunikaty.push_back(tekst);
};

bool Swiat::czyNaMapie(Koordynaty koordynaty) {
    return (
        koordynaty.x >= 0 && koordynaty.x < wymiary.dlugosc &&
        koordynaty.y >= 0 && koordynaty.y < wymiary.wysokosc
    );
};

Swiat::~Swiat() {
    for (Organizm* organizm : organizmy) {
        delete organizm;
    };
};