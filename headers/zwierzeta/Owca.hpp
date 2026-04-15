#ifndef OWCA_HPP
#define OWCA_HPP

#include "../Zwierze.hpp"

class Owca : public Zwierze {
    public:
        Owca(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        ~Owca() = default;
};

#endif