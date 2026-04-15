#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

struct Wymiary {
    int dlugosc;
    int wysokosc;
};

struct Koordynaty {
    int x;
    int y;
};

enum TypOrganizmu {
    ZWIERZE,
    ORGANIZM_CZLOWIEK,
    ROSLINA
};

struct Kierunek {
    int dx;
    int dy;
};

enum TypZwierzecia {
    WILK,
    OWCA,
    LIS,
    ZOLW,
    ANTYLOPA,
    CYBEROWCA,

    CZLOWIEK
};

enum TypRosliny {
    Trawa,
    Mlecz,
    Guarana,
    WilczeJagody,
    BarszczSosnowskiego
};

enum TypKomunikatu {
    NowyOrganizm,
    UsunietoOrganizm,
    Atak,
    Rozmnozenie,
    Smierc,
    Blad,
    InicjalizacjaSwiata,
    ZmianaKoordynatowOrganizmu,
    WykonanieTury
};

#endif