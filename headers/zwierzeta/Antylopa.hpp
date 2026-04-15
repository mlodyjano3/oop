#ifndef ANTYLOPA_HPP
#define ANTYLOPA_HPP

#include "../Zwierze.hpp"

class Antylopa : public Zwierze {
    public:
        Antylopa(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        ~Antylopa() = default;
};

#endif