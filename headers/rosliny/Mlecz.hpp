#ifndef MLECZ_HPP
#define MLECZ_HPP
#include "../Roslina.hpp"

class Mlecz : public Roslina {
public:
    Mlecz(Koordynaty koordynaty, Swiat* swiat);
    char GetSymbol() override;
    void rozrost() override;
    void akcja() override;
    ~Mlecz() = default;
};
#endif