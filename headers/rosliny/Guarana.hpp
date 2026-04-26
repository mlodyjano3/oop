#ifndef GUARANA_HPP
#define GUARANA_HPP
#include "../Roslina.hpp"
class Guarana : public Roslina {
public:
    Guarana(Koordynaty koordynaty, Swiat* swiat);
    char GetSymbol() override;
    void rozrost() override;
    void kolizja(Organizm* atakujacy) override;
    ~Guarana() = default;
};
#endif