
#include "../headers/structures.hpp"
#include "../headers/Swiat.hpp"
#include "../headers/Organizm.hpp"
#include "../headers/parametry.hpp"
#include "../headers/zwierzeta/Czlowiek.hpp"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "../headers/zwierzeta/Czlowiek.hpp"
#include "../headers/zwierzeta/Antylopa.hpp"
#include "../headers/zwierzeta/Cyberowca.hpp"
#include "../headers/zwierzeta/Lis.hpp"
#include "../headers/zwierzeta/Owca.hpp"
#include "../headers/zwierzeta/Wilk.hpp"
#include "../headers/zwierzeta/Zolw.hpp"

#include <fstream>
#include "../headers/rosliny/Trawa.hpp"
#include "../headers/rosliny/Mlecz.hpp"
#include "../headers/rosliny/Guarana.hpp"
#include "../headers/rosliny/WilczeJagody.hpp"
#include "../headers/rosliny/BarszczSosnowskiego.hpp"



Swiat::Swiat(int dlugosc, int wysokosc) {
    this->wymiary.dlugosc = dlugosc;
    this->wymiary.wysokosc = wysokosc;
    this->tura = 1;

    plansza.resize(wymiary.wysokosc, std::vector<Organizm*>(wymiary.dlugosc, nullptr));

    this->czlowiek = new Czlowiek({wymiary.dlugosc / 2, wymiary.wysokosc / 2}, this);

    // init jakichs tam zwierzat na mape
    Zolw *zolw1 = new Zolw({1, 1}, this);
    Zolw *zolw2 = new Zolw({1, 5}, this);

    Lis *lis1 = new Lis({3, 3}, this);
    Lis *lis2 = new Lis({4, 10}, this);

    Antylopa *antylopa1 = new Antylopa({8, 5}, this);
    Antylopa *antylopa2 = new Antylopa({5, 6}, this);

    Wilk *wilk1 = new Wilk({10, 2}, this);
    Wilk *wilk2 = new Wilk({12, 7}, this);

    Owca *owca1 = new Owca({15, 3}, this);
    Owca *owca2 = new Owca({14, 8}, this);

    Cyberowca *cyberowca1 = new Cyberowca({2, 2}, this);
    Cyberowca *cyberowca2 = new Cyberowca({9, 9}, this);
    //

    // dodawanie organizmow do swiata - zwierzeta plus czloiwek
    dodajOrganizm(this->czlowiek);
    dodajOrganizm(zolw1);
    dodajOrganizm(zolw2);
    dodajOrganizm(lis1);
    dodajOrganizm(lis2);
    dodajOrganizm(antylopa1);
    dodajOrganizm(antylopa2);
    dodajOrganizm(wilk1);
    dodajOrganizm(wilk2);
    dodajOrganizm(owca1);
    dodajOrganizm(owca2);
    dodajOrganizm(cyberowca1);
    dodajOrganizm(cyberowca2);


    dodajOrganizm(new Trawa({22, 8}, this));
    dodajOrganizm(new Mlecz({18, 15}, this));
    dodajOrganizm(new Mlecz({25, 20}, this));
    dodajOrganizm(new Guarana({10, 20}, this));
    dodajOrganizm(new Guarana({17, 12}, this));
    dodajOrganizm(new WilczeJagody({7, 25}, this));
    dodajOrganizm(new WilczeJagody({28, 4}, this));
    dodajOrganizm(new BarszczSosnowskiego({20, 20}, this));
    dodajOrganizm(new BarszczSosnowskiego({25, 15}, this));


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
        dodajKomunikat(TypKomunikatu::NowyOrganizm);
    };
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

        organizm->setKoordynaty(noweKoordynaty);
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

const std::vector<Organizm*>& Swiat::getOrganizmy() const {
    return organizmy;
}


void Swiat::wezInputUzytkownika() {
    char znak;
    rysujPoziomaLinie();
    rysujTekst("Ruch: w/a/s/d | Tarcza Alzura: q | Zapis: z | Wczytaj: x");
    std::cin >> znak;

    if (znak == 'q' || znak == 'Q') czlowiek->aktywujUmiejetnosc();
    else if (znak == 'z' || znak == 'Z') zapiszStanSwiata();
    else if (znak == 'x' || znak == 'X') wczytajStanSwiata();
    else czlowiek->ustawKierunek(znak);
}




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

    for (int i=0; i < organizmy.size(); i++ ) {
        if (organizmy[i] != nullptr) { // zjedzony czy nie
            organizmy[i]->akcja();
            if (organizmy[i] != nullptr) { // sprawdzam ponownie zeby zobaczyc czy dany organizm dalej zyje po akjci
                organizmy[i]->zwiekszWiek();
            }
        };
    };

    dodajKomunikat(TypKomunikatu::WykonanieTury);
    tura++;
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

    rysujTekst("Tura: " + std::to_string(tura));
    rysujTekst("Liczba organizmow: " + std::to_string(organizmy.size()));

    // status tarczty alzura
    std::string statusTarczy;
    if (this->czlowiek->getUmiejetnoscAktywna()) {
        statusTarczy = "Tarcza Alzura: AKTYWNA (" +
            std::to_string(this->czlowiek->getTuryAktywnosci()) + " tur pozostalo)";
    } else if (this->czlowiek->getTuryOdnowienia() > 0) {
        statusTarczy = "Tarcza Alzura: cooldown (" +
            std::to_string(this->czlowiek->getTuryOdnowienia()) + " tur)";
    } else {
        statusTarczy = "Tarcza Alzura: gotowa - nacisnij [q]";
    };
    rysujTekst(statusTarczy);

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

void Swiat::dodajKomunikat(std::string tekst) {
    std::string komunikat = "log: " + tekst;
    komunikaty.push_back(komunikat);
};

bool Swiat::czyNaMapie(Koordynaty koordynaty) {
    return (
        koordynaty.x >= 0 && koordynaty.x < wymiary.dlugosc &&
        koordynaty.y >= 0 && koordynaty.y < wymiary.wysokosc
    );
};


// --- fabryka: tworzy organizm na podstawie symbolu z pliku ---
// uzywana wylacznie przez wczytajStanSwiata()
Organizm* Swiat::stworzOrganizm(char symbol, Koordynaty k) {
    switch (symbol) {
        case 'W': return new Wilk(k, this);
        case 'O': return new Owca(k, this);
        case 'L': return new Lis(k, this);
        case 'Z': return new Zolw(k, this);
        case 'A': return new Antylopa(k, this);
        case 'C': return new Cyberowca(k, this);
        case 'T': return new Trawa(k, this);
        case 'M': return new Mlecz(k, this);
        case 'G': return new Guarana(k, this);
        case 'J': return new WilczeJagody(k, this);
        case 'B': return new BarszczSosnowskiego(k, this);
        default:  return nullptr; // nieznany symbol - ignoruj
    };
};

// --- zapis: kazdy organizm jako jedna linia w pliku ---
// format: SYMBOL x y wiek sila [dla & dodatkowo: umiejetnosc turyA turyO]
void Swiat::zapiszStanSwiata() {
    std::ofstream plik(NAZWA_PLIKU_ZAPISU);
    if (!plik.is_open()) {
        this->dodajKomunikat("Blad: nie mozna otworzyc pliku do zapisu!");
        return;
    };

    plik << "TURA " << this->tura << "\n";

    for (Organizm* org : this->organizmy) {
        if (org == nullptr) continue;
        plik << org->GetSymbol() << " "
             << org->getKoordynaty().x << " "
             << org->getKoordynaty().y << " "
             << org->getWiek() << " "
             << org->getSila();
        // dla czlowieka zapisz tez stan tarczy
        if (org->GetSymbol() == '&') {
            plik << " " << this->czlowiek->getUmiejetnoscAktywna()
                 << " " << this->czlowiek->getTuryAktywnosci()
                 << " " << this->czlowiek->getTuryOdnowienia();
        };
        plik << "\n";
    };

    plik.close();
    this->dodajKomunikat("Zapisano stan swiata do pliku " + NAZWA_PLIKU_ZAPISU);
};


void Swiat::wczytajStanSwiata() {
    std::ifstream plik(NAZWA_PLIKU_ZAPISU);
    if (!plik.is_open()) {
        this->dodajKomunikat("Blad: nie mozna otworzyc pliku do odczytu!");
        return;
    };

    // wyczysc stary swiat - usun wszystko oprocz czlowieka (usuwamy go osobno nizej)
    for (Organizm* org : this->organizmy) {
        if (org != nullptr && org != this->czlowiek) delete org;
    };
    if (this->czlowiek != nullptr) delete this->czlowiek;
    this->organizmy.clear();
    for (auto& rzad : this->plansza) std::fill(rzad.begin(), rzad.end(), nullptr);
    this->czlowiek = nullptr;

    // pierwsza linia: numer tury
    std::string linia;
    std::getline(plik, linia);
    this->tura = std::stoi(linia.substr(5)); // "TURA 15" -> 15

    // kolejne linie: organizmy
    while (std::getline(plik, linia)) {
        if (linia.empty()) continue;

        std::istringstream ss(linia);
        char symbol;
        int x, y, wiek, sila;
        ss >> symbol >> x >> y >> wiek >> sila;

        if (symbol == '&') {
            // czlowiek - specjalny przypadek, wczytaj tez stan tarczy
            this->czlowiek = new Czlowiek({x, y}, this);
            this->czlowiek->setWiek(wiek);
            this->czlowiek->setSila(sila);

            bool aktywna = false;
            int turyA = 0, turyO = 0;
            if (ss >> aktywna >> turyA >> turyO) {
                this->czlowiek->wczytajStanUmiejetnosci(aktywna, turyA, turyO);
            };

            // dodaj czlowieka bezposrednio (nie przez dodajOrganizm zeby nie logowac smieci)
            this->plansza[y][x] = this->czlowiek;
            this->organizmy.push_back(this->czlowiek);
        } else {
            // zwykly organizm - uzyj fabryki
            Organizm* org = this->stworzOrganizm(symbol, {x, y});
            if (org != nullptr) {
                org->setWiek(wiek);
                org->setSila(sila);
                this->dodajOrganizm(org);
            };
        };
    };

    plik.close();
    this->dodajKomunikat("Wczytano stan swiata z pliku " + NAZWA_PLIKU_ZAPISU);
};

Swiat::~Swiat() {
    for (Organizm* organizm : organizmy) {
        if (organizm != nullptr) {
            delete organizm;
        };
    };
};