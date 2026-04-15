#ifndef CYBEROWCA_HPP
#define CYBEROWCA_HPP

#include "../Zwierze.hpp"


class Cyberowca : public Zwierze {
    public:
        Cyberowca(Koordynaty koordynaty, Swiat* swiat);
        char GetSymbol() override;
        ~Cyberowca() = default;
};

#endif