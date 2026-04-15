#ifndef CZLOWIEK_HPP
#define CZLOWIEK_HPP

#include "../Zwierze.hpp"


class Czlowiek : public Zwierze {
    private:
        Kierunek kierunekRuchu;

    public:
        Czlowiek(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;

        void ustawKierunek(char znak);
        void akcja() override;
        Kierunek getKierunek() const;

        ~Czlowiek() = default;
};

#endif