#ifndef ZWIERZE_HPP
#define ZWIERZE_HPP

#include "Organizm.hpp"
#include "structures.hpp"

class Zwierze : public Organizm {
    protected:
        TypZwierzecia typZwierzecia;
        
        Zwierze(TypZwierzecia typ, Koordynaty koordynaty, Swiat* swiat);
    public:

        void kolizja(Organizm* kolidujacy) override;
        void akcja() override;

        TypZwierzecia getTypZwierzecia() const;

        virtual ~Zwierze() = default;
};

#endif