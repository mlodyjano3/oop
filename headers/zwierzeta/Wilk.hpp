#ifndef WILK_HPP
#define WILK_HPP


#include "../Zwierze.hpp"

class Wilk : public Zwierze {
    public:
        Wilk(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        ~Wilk() = default;
};

#endif