#ifndef LIS_HPP
#define LIS_HPP

#include "../Zwierze.hpp"

class Lis : public Zwierze {
    public:
        Lis(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        void akcja() override;
        ~Lis() = default;
};

#endif