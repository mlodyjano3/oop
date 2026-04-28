#include <algorithm>
#include <ctime>
#include <dirent.h>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "Swiat.hpp"
#include "../headers/parametry.hpp"

namespace {

void wyczyscEkran() {
    system("clear");
}

void wyczyscWejsciePoBledzie() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int pobierzWybor(int min, int max) {
    while (true) {
        std::cout << "> ";

        int wybor = 0;
        if (std::cin >> wybor && wybor >= min && wybor <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return wybor;
        }

        if (std::cin.eof()) {
            return 0;
        }

        std::cout << "Nieprawidlowy wybor. Sprobuj jeszcze raz.\n";
        wyczyscWejsciePoBledzie();
    }
}

void czekajNaEnter() {
    std::cout << "\nNacisnij Enter, aby wrocic do menu...";
    std::cin.get();
}

std::string polaczSciezke(const std::string& katalog, const std::string& nazwaPliku) {
    if (katalog.empty()) {
        return nazwaPliku;
    }

    if (katalog[katalog.length() - 1] == '/') {
        return katalog + nazwaPliku;
    }

    return katalog + "/" + nazwaPliku;
}

std::string pobierzNazwePliku(const std::string& sciezka) {
    const size_t pozycja = sciezka.find_last_of("/\\");
    if (pozycja == std::string::npos) {
        return sciezka;
    }

    return sciezka.substr(pozycja + 1);
}

bool czyKatalogIstnieje(const std::string& sciezka) {
    struct stat info;
    if (stat(sciezka.c_str(), &info) != 0) {
        return false;
    }

    return S_ISDIR(info.st_mode);
}

bool czyZwyklyPlik(const std::string& sciezka) {
    struct stat info;
    if (stat(sciezka.c_str(), &info) != 0) {
        return false;
    }

    return S_ISREG(info.st_mode);
}

std::vector<std::string> pobierzListePresetow() {
    std::vector<std::string> presety;

    if (!czyKatalogIstnieje(KATALOG_PRESETOW)) {
        return presety;
    }

    DIR* katalog = opendir(KATALOG_PRESETOW.c_str());
    if (katalog == nullptr) {
        return presety;
    }

    dirent* wpis = nullptr;
    while ((wpis = readdir(katalog)) != nullptr) {
        const std::string nazwaPliku = wpis->d_name;
        if (nazwaPliku == "." || nazwaPliku == "..") {
            continue;
        }

        const std::string pelnaSciezka = polaczSciezke(KATALOG_PRESETOW, nazwaPliku);
        if (czyZwyklyPlik(pelnaSciezka)) {
            presety.push_back(pelnaSciezka);
        }
    }

    closedir(katalog);
    std::sort(presety.begin(), presety.end());
    return presety;
}

int pobierzWymiarPlanszy(const std::string& etykieta, int domyslnaWartosc) {
    while (true) {
        std::cout << "Podaj " << etykieta << " planszy";
        std::cout << " (Enter = " << domyslnaWartosc << "): ";

        std::string linia;
        if (!std::getline(std::cin, linia)) {
            return domyslnaWartosc;
        }

        if (linia.empty()) {
            return domyslnaWartosc;
        }

        std::istringstream ss(linia);
        int wartosc = 0;
        char reszta = '\0';
        if ((ss >> wartosc) && !(ss >> reszta) && wartosc >= MINIMALNY_WYMIAR_PLANSZY) {
            return wartosc;
        }

        std::cout << "Nieprawidlowy wymiar. Podaj liczbe calkowita >= "
                  << MINIMALNY_WYMIAR_PLANSZY << ".\n";
    }
}

void uruchomGre(int szerokosc, int wysokosc, const std::string& sciezkaPresetu = "") {
    bool startujDomyslnie = sciezkaPresetu.empty();
    Swiat swiat(szerokosc, wysokosc, startujDomyslnie);

    if (!sciezkaPresetu.empty() && !swiat.wczytajStanSwiata(sciezkaPresetu)) {
        wyczyscEkran();
        std::cout << "Nie udalo sie wczytac presetu: " << sciezkaPresetu << "\n";
        czekajNaEnter();
        return;
    }

    swiat.rysujInterfejs();

    while (!swiat.czyGraSkonczona()) {
        swiat.wezInputUzytkownika();
        if (swiat.czyGraSkonczona()) {
            break;
        }

        swiat.wykonajTure();
        swiat.rysujInterfejs();
    }

    swiat.rysujInterfejs();
    czekajNaEnter();
}

void pokazMenuNowejGry() {
    wyczyscEkran();
    std::cout << "=== Nowa gra ===\n\n";

    int szerokosc = pobierzWymiarPlanszy("szerokosc", SZEROKOSC_PLANSZY);
    int wysokosc = pobierzWymiarPlanszy("wysokosc", WYSOKOSC_PLANSZY);

    uruchomGre(szerokosc, wysokosc);
}

void pokazMenuPresetow() {
    while (true) {
        wyczyscEkran();

        std::vector<std::string> presety = pobierzListePresetow();
        std::cout << "=== Wybierz preset gry ===\n\n";

        if (presety.empty()) {
            std::cout << "Brak presetow w folderze '" << KATALOG_PRESETOW << "'.\n";
            czekajNaEnter();
            return;
        }

        for (size_t i = 0; i < presety.size(); i++) {
            std::cout << (i + 1) << ". " << pobierzNazwePliku(presety[i]) << "\n";
        }
        std::cout << "0. Powrot\n\n";

        std::cout << "Wybierz numer presetu:\n";
        std::cout << "> ";

        int wybor = 0;
        if (!(std::cin >> wybor)) {
            if (std::cin.eof()) {
                return;
            }
            wyczyscWejsciePoBledzie();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (wybor == 0) {
            return;
        }

        if (wybor > 0 && wybor <= static_cast<int>(presety.size())) {
            uruchomGre(SZEROKOSC_PLANSZY, WYSOKOSC_PLANSZY, presety[wybor - 1]);
            return;
        }
    }
}

} // namespace

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    while (true) {
        wyczyscEkran();
        std::cout << "=== Wirtualny Swiat ===\n\n";
        std::cout << "1. Start gry\n";
        std::cout << "2. Wybierz preset gry\n";
        std::cout << "3. Wyjdz\n\n";
        std::cout << "Wybierz opcje:\n";

        int wybor = pobierzWybor(1, 3);
        if (wybor == 0) {
            break;
        }

        if (wybor == 1) {
            pokazMenuNowejGry();
        } else if (wybor == 2) {
            pokazMenuPresetow();
        } else {
            break;
        }
    }

    return 0;
}
