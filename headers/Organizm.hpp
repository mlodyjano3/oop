#ifndef ORGANIZM_HPP
#define ORGANIZM_HPP

#include "structures.hpp"

class Swiat;

class Organizm {
    protected:
        TypOrganizmu typOrganizmu;
        Koordynaty koordynaty;
        int wiek;
        int sila;
        int inicjatywa;
        Swiat* swiat;

    public:
        virtual void akcja() = 0;
        virtual void kolizja(Organizm* atakujacy) = 0;
        virtual char GetSymbol() = 0;

        // Domyslnie zwraca false, uzywane przez zolwia i czlowieka (tarcza)
        virtual bool czyOdbilAtak(Organizm* atakujacy) {
            return false;
        };
        virtual bool czyUciekl(Organizm* atakujacy){
            return false; 
        }

        // gettery / settery
        Koordynaty getKoordynaty() const;
        int getInicjatywa() const;
        int getWiek() const;
        void zwiekszWiek();
        int getSila() const;
        TypOrganizmu getTypOrganizmu() const;

        void setKoordynaty(Koordynaty noweKoordynaty);
        void setSila(int nowaSila);
        void setWiek(int nowyWiek);

        Koordynaty wybierzNoweKoordynaty() const;
        Koordynaty wybierzNoweKoordynatyNoworodka(Organizm* r1, Organizm* r2) const;

        virtual ~Organizm();
};

#endif