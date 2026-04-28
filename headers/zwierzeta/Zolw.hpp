#ifndef ZOLW_HPP
#define ZOLW_HPP

#include "../Zwierze.hpp"

class Zolw : public Zwierze {
    public:
        Zolw(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;

        void akcja() override;

        bool czyOdbilAtak(Organizm* atakujacy) override;

        Organizm* stworzPotomka(Koordynaty k) override;

        ~Zolw() = default;
};

#endif