#ifndef ROSLINA_HPP
#define ROSLINA_HPP

#include "Organizm.hpp"
#include "structures.hpp"


class Roslina : public Organizm {
    public:

        Roslina(TypOrganizmu typ, Koordynaty koordynaty, int sila, int inicjatywa, Swiat* swiat);

        void kolizja(Organizm* atakujacy) override;
        virtual ~Roslina() = default;
        virtual void rozrost() = 0;
        void akcja() override;

    protected:
        
};

#endif