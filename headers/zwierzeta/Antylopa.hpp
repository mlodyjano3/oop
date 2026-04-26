#ifndef ANTYLOPA_HPP
#define ANTYLOPA_HPP

#include "../Zwierze.hpp"

class Antylopa : public Zwierze {
    public:
        Antylopa(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        void akcja() override;
        void kolizja(Organizm* atakujacy) override;
        ~Antylopa() = default;
};

#endif