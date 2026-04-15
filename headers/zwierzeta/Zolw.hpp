#ifndef ZOLW_HPP
#define ZOLW_HPP

#include "../Zwierze.hpp"

class Zolw : public Zwierze {
    public:
        Zolw(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        ~Zolw() = default;
};

#endif