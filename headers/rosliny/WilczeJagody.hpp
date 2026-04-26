#ifndef WILCZEJAGODY_HPP
#define WILCZEJAGODY_HPP
#include "../Roslina.hpp"
class WilczeJagody : public Roslina {
public:
    WilczeJagody(Koordynaty koordynaty, Swiat* swiat);
    char GetSymbol() override;
    void rozrost() override;
    void kolizja(Organizm* atakujacy) override;
    ~WilczeJagody() = default;
};
#endif