#ifndef CZLOWIEK_HPP
#define CZLOWIEK_HPP
#include "../Zwierze.hpp"

class Czlowiek : public Zwierze {
    private:
        Kierunek kierunekRuchu;
        bool umiejetnoscAktywna = false;
        int turyAktywnosci  = 0;
        int turyOdnowienia  = 0;

    public:
        Czlowiek(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;

        void akcja() override;

        bool czyOdbilAtak(Organizm* atakujacy) override;

        Organizm* stworzPotomka(Koordynaty k) override {
            return nullptr;
        };

        void ustawKierunek(char znak);
        void aktywujUmiejetnosc();

        Kierunek getKierunek() const;
        bool getUmiejetnoscAktywna() const { return umiejetnoscAktywna; }
        int  getTuryAktywnosci() const { return turyAktywnosci;     }
        int  getTuryOdnowienia() const { return turyOdnowienia;     }

        void wczytajStanUmiejetnosci(bool a, int tA, int tO) {
            umiejetnoscAktywna = a; turyAktywnosci = tA; turyOdnowienia = tO;
        }
        ~Czlowiek() = default;
};
#endif