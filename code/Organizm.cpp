#include "../headers/Organizm.hpp"
#include "../headers/Swiat.hpp"
#include "math.h"
#include <cstdlib>
#include <vector>



Organizm::~Organizm() {}

Koordynaty Organizm::getKoordynaty() const {
    return this->koordynaty;
}

int Organizm::getInicjatywa() const {
    return this->inicjatywa;
}

int Organizm::getWiek() const {
    return this->wiek;
}

void Organizm::zwiekszWiek() {
    this->wiek++;
}

int Organizm::getSila() const {
    return this->sila;
}

Koordynaty Organizm::wybierzNoweKoordynaty() const {
    Koordynaty stareKoordynaty = this->getKoordynaty();

    Koordynaty mozliwosci[8] = {
        {stareKoordynaty.x - 1, stareKoordynaty.y - 1},
        {stareKoordynaty.x - 1, stareKoordynaty.y},
        {stareKoordynaty.x - 1, stareKoordynaty.y + 1},
        {stareKoordynaty.x, stareKoordynaty.y - 1},
        {stareKoordynaty.x, stareKoordynaty.y + 1},
        {stareKoordynaty.x + 1, stareKoordynaty.y - 1},
        {stareKoordynaty.x + 1, stareKoordynaty.y},
        {stareKoordynaty.x + 1, stareKoordynaty.y + 1}
    };

    std::vector<Koordynaty> dostepneMozliwosci;
    for ( int i = 0; i < 8; i++ ) {
        Koordynaty potencjalneKoordynaty = mozliwosci[i];
        if ( swiat->czyNaMapie(potencjalneKoordynaty) ) {
            /*
            if ( swiat->czyWolne(potencjalneKoordynaty) ) {
                
            };
            */ // zakomentowane bo nie musi byc wolne, moze byc kolizja 
            dostepneMozliwosci.push_back(potencjalneKoordynaty);
        };
    };

    int rozmiar = dostepneMozliwosci.size();
    if ( rozmiar > 0) {

        int losowyIndex = rand() % rozmiar;

        return dostepneMozliwosci[losowyIndex];

    } else {
        return stareKoordynaty;
    };
};