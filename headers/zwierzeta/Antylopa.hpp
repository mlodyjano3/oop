#ifndef ANTYLOPA_HPP
#define ANTYLOPA_HPP

#include "../Zwierze.hpp"

class Antylopa : public Zwierze {
    public:
        Antylopa(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        void akcja() override; // zasieg 2 pol

        bool czyUciekl(Organizm* atakujacy) override;

        Organizm* stworzPotomka(Koordynaty k) override;

        ~Antylopa() = default;
};

#endif