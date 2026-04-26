#ifndef TRAWA_HPP
#define TRAWA_HPP
#include "../Roslina.hpp"

class Trawa : public Roslina {
public:
    Trawa(Koordynaty koordynaty, Swiat* swiat);
    char GetSymbol() override;
    void rozrost() override;
    ~Trawa() = default;
};
#endif