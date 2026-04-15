#ifndef PARAMETRY_HPP
#define PARAMETRY_HPP



// ------------------------------------------------------------------------
// stale dla swiata

const char DEKORATOR_POZIOMY = '=';
const char DEKORATOR_PIONOWY = '|';

const int PIXELE_PER_POLE = 1 + 2; // 1 na znak + 2 na padding

const int WYSOKOSC_PLANSZY = 20; // ile pol jest na planszy
const int SZEROKOSC_PLANSZY = 20;

const int ILOSC_PIXELI_NA_MAPIE = WYSOKOSC_PLANSZY * SZEROKOSC_PLANSZY * PIXELE_PER_POLE * PIXELE_PER_POLE;

const int ILOSC_PIXELI_NA_POLE = PIXELE_PER_POLE * PIXELE_PER_POLE;
const int ILOSC_POL_NA_MAPIE = WYSOKOSC_PLANSZY * SZEROKOSC_PLANSZY;

const int SZEROKOSC_MAPY_W_PIXELACH = SZEROKOSC_PLANSZY * PIXELE_PER_POLE;
const int WYSOKOSC_MAPY_W_PIXELACH = WYSOKOSC_PLANSZY * PIXELE_PER_POLE;

const int MAX_ROSLIN = 10;
const int MAX_ZWIERZAT = 10;
const int MAX_ORGANIZMOW_LACZNIE = MAX_ROSLIN + MAX_ZWIERZAT;


const int WYSOKOSC_INTERFEJSU_PIXELE = 30;
const int SZEROKOSC_INTERFEJSU_PIXELE = SZEROKOSC_MAPY_W_PIXELACH;

const int MAX_KOMUNIKATOW = 10;
const int WYSOKOSC_KOMUNIKATOW_PIXELE = MAX_KOMUNIKATOW;
const int SZEROKOSC_KOMUNIKATOW_PIXELE = SZEROKOSC_MAPY_W_PIXELACH;


// na gorna ramke, ramke miedzy plansza a interfejsem, ramke miedzy intefejsem a komunikatami, dolna rame
const int WYSOKOSC_OKNA = WYSOKOSC_MAPY_W_PIXELACH + WYSOKOSC_INTERFEJSU_PIXELE + WYSOKOSC_KOMUNIKATOW_PIXELE + 1 + 1 + 1 + 1;
const int SZEROKOSC_OKNA = SZEROKOSC_PLANSZY * PIXELE_PER_POLE+ 2;



// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
// stale dla zwierzat 

const int SILA_CZLOWIEK = 5;
const int INICJATYWA_CZLOWIEK = 4;

const int SILA_WILK = 9;
const int INICJATYWA_WILK = 5;

const int SILA_OWCA = 4;
const int INICJATYWA_OWCA = 4;

const int SILA_LIS = 3;
const int INICJATYWA_LIS = 7;

const int SILA_ZOLW = 2;
const int INICJATYWA_ZOLW = 1;

const int SILA_ANTYLOPA = 4;
const int INICJATYWA_ANTYLOPA = 4;

const int SILA_CYBEROWCA = 10;
const int INICJATYWA_CYBEROWCA = 4;

// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//stale dla roslin

const int SILA_TRAWA = 0;
const int SILA_MLECZ = 0;
const int SILA_GUARANA = 0;
const int SILA_WILCZE_JAGODY = 99;
const int SILA_BARSZCZ_SOSNOWSKIEGO = 10;


#endif