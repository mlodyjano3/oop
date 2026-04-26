#include "../headers/Roslina.hpp"
#include "../headers/Swiat.hpp"

Roslina::Roslina(TypOrganizmu typ, Koordynaty koordynaty, int sila, int inicjatywa, Swiat* swiat) {
    this->typOrganizmu = typ;
    this->koordynaty = koordynaty;
    this->sila = sila;
    this->inicjatywa = inicjatywa;
    this->swiat = swiat;
    this->wiek = 0;
};

void Roslina::kolizja(Organizm* atakujacy) {
    // domyslnie poprostu ginie

    swiat->dodajKomunikat("Roslina na (" + std::to_string(koordynaty.x) + "," + std::to_string(koordynaty.y) + ") zostala zjedzona");
    swiat->usunOrganizm(this);
};

void Roslina::akcja() {
    rozrost(); // kazda roslina wie co robi jej rozrost()
}