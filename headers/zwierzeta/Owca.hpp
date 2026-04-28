#ifndef OWCA_HPP
#define OWCA_HPP

#include "../Zwierze.hpp"

class Owca : public Zwierze {
    public:
        Owca(Koordynaty koordynaty, Swiat* swiat);
        Organizm* stworzPotomka(Koordynaty k) override;
        
        char GetSymbol() override;
        ~Owca() = default;
};

#endif