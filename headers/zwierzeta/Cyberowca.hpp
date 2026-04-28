#ifndef CYBEROWCA_HPP
#define CYBEROWCA_HPP

#include "../Zwierze.hpp"


class Cyberowca : public Zwierze {
    public:
        Organizm* stworzPotomka(Koordynaty k) override;
        Cyberowca(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        void akcja() override;
        ~Cyberowca() = default;
};

#endif