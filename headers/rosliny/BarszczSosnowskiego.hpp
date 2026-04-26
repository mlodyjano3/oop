#ifndef BARSZCZ_HPP
#define BARSZCZ_HPP
#include "../Roslina.hpp"
class Cyberowca; // forward declaration
class BarszczSosnowskiego : public Roslina {
public:
    BarszczSosnowskiego(Koordynaty koordynaty, Swiat* swiat);
    char GetSymbol() override;
    void rozrost() override;
    void akcja() override;
    void kolizja(Organizm* atakujacy) override;
    ~BarszczSosnowskiego() = default;
};
#endif