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
        // Organizm(Koordynaty koordynaty, Swiat* swiat);
        
        // musza byc bo tak kaze instrukcja
        virtual void akcja() = 0;
        virtual void kolizja(Organizm* atakujacy) = 0;
        virtual char GetSymbol() = 0;
        // virtual void rysowanie() = 0; // imo useless bo zrobilbym to w rysujSwiat 

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
        Koordynaty wybierzNoweKoordynatyNoworodka(Organizm* rodzic, Organizm* rodzic2) const;
        


        virtual ~Organizm();
};

#endif