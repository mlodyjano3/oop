#include "../headers/structures.hpp"
#include "../headers/Swiat.hpp"
#include "../headers/Organizm.hpp"
#include "../headers/parametry.hpp"
#include "../headers/zwierzeta/Czlowiek.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "../headers/rosliny/BarszczSosnowskiego.hpp"
#include "../headers/rosliny/Guarana.hpp"
#include "../headers/rosliny/Mlecz.hpp"
#include "../headers/rosliny/Trawa.hpp"
#include "../headers/rosliny/WilczeJagody.hpp"
#include "../headers/zwierzeta/Antylopa.hpp"
#include "../headers/zwierzeta/Cyberowca.hpp"
#include "../headers/zwierzeta/Lis.hpp"
#include "../headers/zwierzeta/Owca.hpp"
#include "../headers/zwierzeta/Wilk.hpp"
#include "../headers/zwierzeta/Zolw.hpp"

Swiat::Swiat(int dlugosc, int wysokosc, bool inicjalizujDomyslnie)
    : tura(1), graSkonczona(false), czlowiek(nullptr) {
    ustawRozmiarPlanszy(dlugosc, wysokosc);

    if (inicjalizujDomyslnie) {
        inicjalizujDomyslneOrganizmy();
        dodajKomunikat(TypKomunikatu::InicjalizacjaSwiata);
    }
}

void Swiat::ustawRozmiarPlanszy(int dlugosc, int wysokosc) {
    wymiary.dlugosc = std::max(MINIMALNY_WYMIAR_PLANSZY, dlugosc);
    wymiary.wysokosc = std::max(MINIMALNY_WYMIAR_PLANSZY, wysokosc);
    plansza.assign(
        wymiary.wysokosc,
        std::vector<Organizm*>(wymiary.dlugosc, nullptr)
    );
}

void Swiat::wyczyscSwiat() {
    for (Organizm* organizm : organizmy) {
        if (organizm != nullptr) {
            delete organizm;
        }
    }

    organizmy.clear();
    for (auto& rzad : plansza) {
        std::fill(rzad.begin(), rzad.end(), nullptr);
    }

    czlowiek = nullptr;
    graSkonczona = false;
    komunikatKonca.clear();
}

void Swiat::usunPusteWpisy() {
    organizmy.erase(
        std::remove(organizmy.begin(), organizmy.end(), nullptr),
        organizmy.end()
    );
}

int Swiat::getDlugosc() const {
    return wymiary.dlugosc;
}

int Swiat::getWysokosc() const {
    return wymiary.wysokosc;
}

int Swiat::getTura() const {
    return tura;
}

int Swiat::getPojemnoscPlanszy() const {
    return wymiary.dlugosc * wymiary.wysokosc;
}

int Swiat::getLiczbaOrganizmow() const {
    int licznik = 0;
    for (Organizm* organizm : organizmy) {
        if (organizm != nullptr) {
            licznik++;
        }
    }
    return licznik;
}

int Swiat::getLiczbaRoslin() const {
    int licznik = 0;
    for (Organizm* organizm : organizmy) {
        if (organizm != nullptr && organizm->getTypOrganizmu() == ROSLINA) {
            licznik++;
        }
    }
    return licznik;
}

int Swiat::getLiczbaZwierzat() const {
    int licznik = 0;
    for (Organizm* organizm : organizmy) {
        if (organizm != nullptr && organizm->getTypOrganizmu() == ZWIERZE) {
            licznik++;
        }
    }
    return licznik;
}

int Swiat::getMaksLiczbaRoslin() const {
    int limitDynamiczny = getPojemnoscPlanszy() / DZIELNIK_LIMITU_ROSLIN;
    return std::min(getPojemnoscPlanszy(), std::max(MAX_ROSLIN, limitDynamiczny));
}

int Swiat::getMaksLiczbaZwierzat() const {
    int limitDynamiczny = getPojemnoscPlanszy() / DZIELNIK_LIMITU_ZWIERZAT;
    return std::min(getPojemnoscPlanszy(), std::max(MAX_ZWIERZAT, limitDynamiczny));
}

bool Swiat::czyGraSkonczona() const {
    return graSkonczona;
}

const std::string& Swiat::getKomunikatKonca() const {
    return komunikatKonca;
}

const std::vector<Organizm*>& Swiat::getOrganizmy() const {
    return organizmy;
}

Czlowiek* Swiat::getCzlowiek() const {
    return czlowiek;
}

bool Swiat::czyMoznaDodacOrganizm(Organizm* organizm) const {
    if (organizm == nullptr) {
        return false;
    }

    if (getLiczbaOrganizmow() >= getPojemnoscPlanszy()) {
        return false;
    }

    if (organizm->getTypOrganizmu() == ROSLINA) {
        return getLiczbaRoslin() < getMaksLiczbaRoslin();
    }

    if (organizm->getTypOrganizmu() == ZWIERZE) {
        bool toCzlowiek = dynamic_cast<Czlowiek*>(organizm) != nullptr;
        int liczbaZwierzatBezCzlowieka = getLiczbaZwierzat() - (czlowiek != nullptr ? 1 : 0);
        return toCzlowiek || liczbaZwierzatBezCzlowieka < getMaksLiczbaZwierzat();
    }

    return true;
}

bool Swiat::dodajOrganizmWewnetrznie(Organizm* organizm, bool ignorujLimity) {
    if (organizm == nullptr) {
        return false;
    }

    Koordynaty k = organizm->getKoordynaty();

    if (!czyNaMapie(k)) {
        delete organizm;
        return false;
    }

    if (plansza[k.y][k.x] != nullptr) {
        delete organizm;
        return false;
    }

    if (!ignorujLimity && !czyMoznaDodacOrganizm(organizm)) {
        delete organizm;
        return false;
    }

    plansza[k.y][k.x] = organizm;
    organizmy.push_back(organizm);

    Czlowiek* nowyCzlowiek = dynamic_cast<Czlowiek*>(organizm);
    if (nowyCzlowiek != nullptr) {
        czlowiek = nowyCzlowiek;
    }

    dodajKomunikat(TypKomunikatu::NowyOrganizm);
    return true;
}

void Swiat::dodajOrganizm(Organizm* organizm) {
    dodajOrganizmWewnetrznie(organizm, false);
}

void Swiat::usunOrganizm(Organizm* organizm) {
    if (organizm == nullptr) {
        return;
    }

    Koordynaty koordynatyOrganizmu = organizm->getKoordynaty();
    if (czyNaMapie(koordynatyOrganizmu) &&
        plansza[koordynatyOrganizmu.y][koordynatyOrganizmu.x] == organizm) {
        plansza[koordynatyOrganizmu.y][koordynatyOrganizmu.x] = nullptr;
    }

    for (size_t i = 0; i < organizmy.size(); i++) {
        if (organizmy[i] == organizm) {
            organizmy[i] = nullptr;
            break;
        }
    }

    if (organizm == czlowiek) {
        czlowiek = nullptr;
        graSkonczona = true;
        komunikatKonca = "Koniec gry: czlowiek zginal";
        dodajKomunikat(komunikatKonca);
    }

    delete organizm;
    dodajKomunikat(TypKomunikatu::UsunietoOrganizm);
}

bool Swiat::porownajOrganizmy(Organizm* a, Organizm* b) {
    if (a == nullptr) return false;
    if (b == nullptr) return true;

    if (a->getInicjatywa() != b->getInicjatywa()) {
        return a->getInicjatywa() > b->getInicjatywa();
    }

    return a->getWiek() > b->getWiek();
}

bool Swiat::zmienKoordynatyOrganizmu(Organizm* organizm, Koordynaty noweKoordynaty) {
    if (organizm == nullptr || !czyWolne(noweKoordynaty)) {
        return false;
    }

    Koordynaty stareKoordynaty = organizm->getKoordynaty();

    if (czyNaMapie(stareKoordynaty) &&
        plansza[stareKoordynaty.y][stareKoordynaty.x] == organizm) {
        plansza[stareKoordynaty.y][stareKoordynaty.x] = nullptr;
    }

    plansza[noweKoordynaty.y][noweKoordynaty.x] = organizm;
    organizm->setKoordynaty(noweKoordynaty);
    return true;
}

Organizm* Swiat::getOrganizmAt(Koordynaty koordynaty) const {
    if (!czyNaMapie(koordynaty)) {
        return nullptr;
    }

    return plansza[koordynaty.y][koordynaty.x];
}

bool Swiat::czyWolne(Koordynaty koordynaty) const {
    if (!czyNaMapie(koordynaty)) {
        return false;
    }

    return plansza[koordynaty.y][koordynaty.x] == nullptr;
}

bool Swiat::czyNaMapie(Koordynaty koordynaty) const {
    return (
        koordynaty.x >= 0 && koordynaty.x < wymiary.dlugosc &&
        koordynaty.y >= 0 && koordynaty.y < wymiary.wysokosc
    );
}

Koordynaty Swiat::znajdzLosoweWolnePole() const {
    std::vector<Koordynaty> wolnePola;

    for (int y = 0; y < wymiary.wysokosc; y++) {
        for (int x = 0; x < wymiary.dlugosc; x++) {
            if (plansza[y][x] == nullptr) {
                wolnePola.push_back({x, y});
            }
        }
    }

    if (wolnePola.empty()) {
        return {-1, -1};
    }

    return wolnePola[rand() % wolnePola.size()];
}

Koordynaty Swiat::znajdzNajblizszeWolnePoleOdSrodka() const {
    Koordynaty srodek = {wymiary.dlugosc / 2, wymiary.wysokosc / 2};
    if (czyWolne(srodek)) {
        return srodek;
    }

    Koordynaty najlepsze = {-1, -1};
    int najlepszyDystans = getPojemnoscPlanszy() + 1;

    for (int y = 0; y < wymiary.wysokosc; y++) {
        for (int x = 0; x < wymiary.dlugosc; x++) {
            if (plansza[y][x] != nullptr) {
                continue;
            }

            int dystans = std::abs(x - srodek.x) + std::abs(y - srodek.y);
            if (dystans < najlepszyDystans) {
                najlepszyDystans = dystans;
                najlepsze = {x, y};
            }
        }
    }

    return najlepsze;
}

void Swiat::inicjalizujDomyslneOrganizmy() {
    wyczyscSwiat();
    komunikaty.clear();
    tura = 1;

    Koordynaty pozycjaCzlowieka = znajdzNajblizszeWolnePoleOdSrodka();
    if (pozycjaCzlowieka.x != -1) {
        dodajOrganizmWewnetrznie(new Czlowiek(pozycjaCzlowieka, this), true);
    }

    const std::vector<char> startoweSymbole = {
        'Z', 'Z',
        'L', 'L',
        'A', 'A',
        'W', 'W',
        'O', 'O',
        'C', 'C',
        'T',
        'M', 'M',
        'G', 'G',
        'J', 'J',
        'B', 'B'
    };

    for (char symbol : startoweSymbole) {
        Koordynaty k = znajdzLosoweWolnePole();
        if (k.x == -1) {
            break;
        }

        dodajOrganizmWewnetrznie(stworzOrganizm(symbol, k), true);
    }
}

void Swiat::wezInputUzytkownika() {
    if (graSkonczona) {
        return;
    }

    char znak = '\0';
    rysujPoziomaLinie();
    rysujTekst("Ruch: w/a/s/d | Tarcza Alzura: q | Zapis: z | Wczytaj: x");

    if (!(std::cin >> znak)) {
        graSkonczona = true;
        if (komunikatKonca.empty()) {
            komunikatKonca = "Zakonczenie gry";
        }
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (znak == 'q' || znak == 'Q') {
        if (czlowiek != nullptr) {
            czlowiek->aktywujUmiejetnosc();
        }
    } else if (znak == 'z' || znak == 'Z') {
        zapiszStanSwiata();
    } else if (znak == 'x' || znak == 'X') {
        wczytajStanSwiata();
    } else if (czlowiek != nullptr) {
        czlowiek->ustawKierunek(znak);
    } else {
        dodajKomunikat("Czlowiek nie zyje - ruch jest niemozliwy");
    }
}

void Swiat::wykonajTure() {
    if (graSkonczona) {
        return;
    }

    usunPusteWpisy();

    std::sort(organizmy.begin(), organizmy.end(), [](Organizm* a, Organizm* b) {
        if (a == nullptr) return false;
        if (b == nullptr) return true;
        if (a->getInicjatywa() != b->getInicjatywa()) {
            return a->getInicjatywa() > b->getInicjatywa();
        }
        return a->getWiek() > b->getWiek();
    });

    const int rozmiarTury = static_cast<int>(organizmy.size());
    for (int i = 0; i < rozmiarTury; i++) {
        Organizm* aktywny = organizmy[i];
        if (aktywny == nullptr) {
            continue;
        }

        aktywny->akcja();

        if (graSkonczona) {
            break;
        }

        if (i < static_cast<int>(organizmy.size()) && organizmy[i] == aktywny) {
            aktywny->zwiekszWiek();
        }
    }

    usunPusteWpisy();

    if (!graSkonczona) {
        dodajKomunikat(TypKomunikatu::WykonanieTury);
        tura++;
    }
}

int Swiat::getSzerokoscOkna() const {
    int szerokoscMapy = wymiary.dlugosc * PIXELE_PER_POLE + 2;
    int najdluzszaLinia = 0;

    const std::vector<std::string> staleLinie = {
        "Autor: Jan Krol, Indeks: 208228",
        "Grupa: 7A, Projekt: Swiat w cpp",
        "Legenda:",
        "& - Czlowiek, . - Puste pole",
        "A - Antylopa, W - Wilk, O - Owca, L - Lis, Z - Zolw",
        "T - Trawa, M - Mlecz, G - Guarana",
        "J - Wilcze jagody, B - Barszcz",
        "Ruch: w/a/s/d | Tarcza Alzura: q | Zapis: z | Wczytaj: x"
    };

    for (const std::string& linia : staleLinie) {
        najdluzszaLinia = std::max(najdluzszaLinia, static_cast<int>(linia.length()));
    }

    najdluzszaLinia = std::max(
        najdluzszaLinia,
        static_cast<int>(("Tura: " + std::to_string(tura)).length())
    );
    najdluzszaLinia = std::max(
        najdluzszaLinia,
        static_cast<int>(("Liczba organizmow: " + std::to_string(getLiczbaOrganizmow())).length())
    );
    najdluzszaLinia = std::max(
        najdluzszaLinia,
        static_cast<int>(("Rosliny: " + std::to_string(getLiczbaRoslin()) +
            " / limit " + std::to_string(getMaksLiczbaRoslin())).length())
    );
    najdluzszaLinia = std::max(
        najdluzszaLinia,
        static_cast<int>(("Zwierzeta: " + std::to_string(getLiczbaZwierzat()) +
            " / limit " + std::to_string(getMaksLiczbaZwierzat())).length())
    );
    najdluzszaLinia = std::max(
        najdluzszaLinia,
        static_cast<int>(komunikatKonca.length())
    );

    int poczatek = std::max(0, static_cast<int>(komunikaty.size()) - MAX_KOMUNIKATOW);
    for (int i = poczatek; i < static_cast<int>(komunikaty.size()); i++) {
        najdluzszaLinia = std::max(
            najdluzszaLinia,
            static_cast<int>(komunikaty[i].length())
        );
    }

    return std::max(szerokoscMapy, najdluzszaLinia + 4);
}

void Swiat::rysujPoziomaLinie() {
    for (int i = 0; i < getSzerokoscOkna(); i++) {
        std::cout << DEKORATOR_POZIOMY;
    }
    std::cout << std::endl;
}

void Swiat::rysujTekst(std::string text) {
    const int szerokosc = getSzerokoscOkna();
    const int miejsceNaTekst = std::max(0, szerokosc - 4);

    if (static_cast<int>(text.length()) > miejsceNaTekst) {
        text = text.substr(0, miejsceNaTekst);
    }

    std::cout << DEKORATOR_PIONOWY << " " << text;

    int pozostaleSpacje = szerokosc - static_cast<int>(text.length()) - 3;
    for (int i = 0; i < pozostaleSpacje; i++) {
        std::cout << " ";
    }

    std::cout << DEKORATOR_PIONOWY << std::endl;
}

void Swiat::rysujKomunikaty() {
    int total = static_cast<int>(komunikaty.size());
    int poczatek = std::max(0, total - MAX_KOMUNIKATOW);

    for (int i = total - 1; i >= poczatek; i--) {
        rysujTekst(komunikaty[i]);
    }
}

void Swiat::rysujSwiat() {
    const int szerokosc = getSzerokoscOkna();
    const int szerokoscWierszaMapy = wymiary.dlugosc * PIXELE_PER_POLE;
    const int padding = std::max(0, szerokosc - szerokoscWierszaMapy - 2);

    for (int y = 0; y < wymiary.wysokosc; y++) {
        std::cout << DEKORATOR_PIONOWY;
        for (int x = 0; x < wymiary.dlugosc; x++) {
            std::cout << " " << (plansza[y][x] != nullptr ? plansza[y][x]->GetSymbol() : '.') << " ";
        }
        for (int i = 0; i < padding; i++) {
            std::cout << " ";
        }
        std::cout << DEKORATOR_PIONOWY << std::endl;
    }
}

void Swiat::rysujInterfejs() {
    system("clear");

    rysujPoziomaLinie();
    rysujTekst("Autor: Jan Krol, Indeks: 208228");
    rysujTekst("Grupa: 7A, Projekt: Swiat w cpp");
    rysujTekst("Legenda:");
    rysujTekst("& - Czlowiek, . - Puste pole");
    rysujTekst("A - Antylopa, W - Wilk, O - Owca, L - Lis, Z - Zolw");
    rysujTekst("T - Trawa, M - Mlecz, G - Guarana");
    rysujTekst("J - Wilcze jagody, B - Barszcz");

    rysujPoziomaLinie();
    rysujTekst("Tura: " + std::to_string(tura));
    rysujTekst("Liczba organizmow: " + std::to_string(getLiczbaOrganizmow()));
    rysujTekst("Rosliny: " + std::to_string(getLiczbaRoslin()) +
        " / limit " + std::to_string(getMaksLiczbaRoslin()));
    rysujTekst("Zwierzeta: " + std::to_string(getLiczbaZwierzat()) +
        " / limit " + std::to_string(getMaksLiczbaZwierzat()));

    std::string status;
    if (graSkonczona) {
        status = komunikatKonca;
    } else if (czlowiek != nullptr) {
        if (czlowiek->getUmiejetnoscAktywna()) {
            status = "Tarcza Alzura: AKTYWNA (" +
                std::to_string(czlowiek->getTuryAktywnosci()) + " tur pozostalo)";
        } else if (czlowiek->getTuryOdnowienia() > 0) {
            status = "Tarcza Alzura: cooldown (" +
                std::to_string(czlowiek->getTuryOdnowienia()) + " tur)";
        } else {
            status = "Tarcza Alzura: gotowa - nacisnij [q]";
        }
    }

    rysujTekst(status);
    rysujPoziomaLinie();
    rysujSwiat();
    rysujPoziomaLinie();
    rysujKomunikaty();
    rysujPoziomaLinie();
}

void Swiat::dodajKomunikat(TypKomunikatu typ) {
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
    }

    dodajKomunikat(tekst.substr(5));
}

void Swiat::dodajKomunikat(std::string tekst) {
    komunikaty.push_back("log: " + tekst);

    if (static_cast<int>(komunikaty.size()) > MAX_ZAPAMIETANYCH_KOMUNIKATOW) {
        komunikaty.erase(
            komunikaty.begin(),
            komunikaty.begin() + (komunikaty.size() - MAX_ZAPAMIETANYCH_KOMUNIKATOW)
        );
    }
}

Organizm* Swiat::stworzOrganizm(char symbol, Koordynaty k) {
    switch (symbol) {
        case '&': return new Czlowiek(k, this);
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
        default:  return nullptr;
    }
}

void Swiat::zapiszStanSwiata() {
    zapiszStanSwiata(NAZWA_PLIKU_ZAPISU);
}

void Swiat::zapiszStanSwiata(const std::string& sciezka) {
    usunPusteWpisy();

    std::ofstream plik(sciezka);
    if (!plik.is_open()) {
        dodajKomunikat("Blad: nie mozna otworzyc pliku do zapisu!");
        return;
    }

    plik << "ROZMIAR " << wymiary.dlugosc << " " << wymiary.wysokosc << "\n";
    plik << "TURA " << tura << "\n";

    for (Organizm* org : organizmy) {
        if (org == nullptr) {
            continue;
        }

        plik << org->GetSymbol() << " "
             << org->getKoordynaty().x << " "
             << org->getKoordynaty().y << " "
             << org->getWiek() << " "
             << org->getSila();

        Czlowiek* zapisanyCzlowiek = dynamic_cast<Czlowiek*>(org);
        if (zapisanyCzlowiek != nullptr) {
            plik << " " << zapisanyCzlowiek->getUmiejetnoscAktywna()
                 << " " << zapisanyCzlowiek->getTuryAktywnosci()
                 << " " << zapisanyCzlowiek->getTuryOdnowienia();
        }

        plik << "\n";
    }

    dodajKomunikat("Zapisano stan swiata do pliku " + sciezka);
}

bool Swiat::wczytajStanSwiata() {
    return wczytajStanSwiata(NAZWA_PLIKU_ZAPISU);
}

bool Swiat::wczytajStanSwiata(const std::string& sciezka) {
    std::ifstream plik(sciezka);
    if (!plik.is_open()) {
        dodajKomunikat("Blad: nie mozna otworzyc pliku do odczytu!");
        return false;
    }

    std::string linia;
    int nowaDlugosc = wymiary.dlugosc;
    int nowaWysokosc = wymiary.wysokosc;
    int nowaTura = 1;

    if (!std::getline(plik, linia)) {
        dodajKomunikat("Blad: pusty plik zapisu!");
        return false;
    }

    if (linia.rfind("ROZMIAR ", 0) == 0) {
        std::istringstream ss(linia.substr(8));
        if (!(ss >> nowaDlugosc >> nowaWysokosc)) {
            dodajKomunikat("Blad: nieprawidlowy rozmiar planszy w pliku!");
            return false;
        }

        if (!std::getline(plik, linia)) {
            dodajKomunikat("Blad: brak informacji o turze!");
            return false;
        }
    }

    if (linia.rfind("TURA ", 0) != 0) {
        dodajKomunikat("Blad: nieprawidlowy format pliku zapisu!");
        return false;
    }

    try {
        nowaTura = std::stoi(linia.substr(5));
    } catch (...) {
        dodajKomunikat("Blad: nie mozna odczytac numeru tury!");
        return false;
    }

    std::vector<std::string> linieOrganizmow;
    while (std::getline(plik, linia)) {
        if (!linia.empty()) {
            linieOrganizmow.push_back(linia);
        }
    }

    wyczyscSwiat();
    ustawRozmiarPlanszy(nowaDlugosc, nowaWysokosc);
    komunikaty.clear();
    tura = nowaTura;

    for (const std::string& wpis : linieOrganizmow) {
        std::istringstream ss(wpis);
        char symbol = '\0';
        int x = 0;
        int y = 0;
        int wiek = 0;
        int sila = 0;

        if (!(ss >> symbol >> x >> y >> wiek >> sila)) {
            dodajKomunikat("Pominieto uszkodzona linie pliku: " + wpis);
            continue;
        }

        Organizm* org = stworzOrganizm(symbol, {x, y});
        if (org == nullptr) {
            dodajKomunikat("Pominieto nieznany symbol organizmu: " + std::string(1, symbol));
            continue;
        }

        org->setWiek(wiek);
        org->setSila(sila);

        Czlowiek* wczytanyCzlowiek = dynamic_cast<Czlowiek*>(org);
        if (wczytanyCzlowiek != nullptr) {
            bool aktywna = false;
            int turyA = 0;
            int turyO = 0;
            if (ss >> aktywna >> turyA >> turyO) {
                wczytanyCzlowiek->wczytajStanUmiejetnosci(aktywna, turyA, turyO);
            }
        }

        if (!dodajOrganizmWewnetrznie(org, true)) {
            dodajKomunikat("Pominieto organizm spoza planszy lub na zajetym polu");
        }
    }

    if (czlowiek == nullptr) {
        Koordynaty pozycjaCzlowieka = znajdzNajblizszeWolnePoleOdSrodka();
        if (pozycjaCzlowieka.x != -1) {
            dodajOrganizmWewnetrznie(new Czlowiek(pozycjaCzlowieka, this), true);
            dodajKomunikat("Ostrzezenie: brak czlowieka w pliku - stworzono domyslnego");
        } else {
            graSkonczona = true;
            komunikatKonca = "Brak miejsca na czlowieka";
        }
    }

    dodajKomunikat("Wczytano stan swiata z pliku " + sciezka);
    return true;
}

Swiat::~Swiat() {
    wyczyscSwiat();
}
