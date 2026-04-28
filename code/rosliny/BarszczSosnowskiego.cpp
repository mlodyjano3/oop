#include "../../headers/rosliny/BarszczSosnowskiego.hpp"
#include "../../headers/zwierzeta/Cyberowca.hpp"
#include "../../headers/Swiat.hpp"
#include "../../headers/parametry.hpp"
#include <vector>
#include <cstdlib>

BarszczSosnowskiego::BarszczSosnowskiego(Koordynaty k, Swiat* s) 
    : Roslina(ROSLINA, k, SILA_BARSZCZ_SOSNOWSKIEGO, 0, s) {}

char BarszczSosnowskiego::GetSymbol() { return 'B'; }

void BarszczSosnowskiego::rozrost() {
    if (rand() % 5 != 0) return;
    Koordynaty cel = this->wybierzNoweKoordynaty();
    if (cel.x == koordynaty.x && cel.y == koordynaty.y) return;
    if (!swiat->czyWolne(cel)) return;
    swiat->dodajOrganizm(new BarszczSosnowskiego(cel, swiat));
}

void BarszczSosnowskiego::akcja() {
    Koordynaty stare = this->koordynaty;
    Koordynaty sasiedzi[8] = {
        {stare.x-1,stare.y-1},{stare.x-1,stare.y},{stare.x-1,stare.y+1},
        {stare.x,stare.y-1},{stare.x,stare.y+1},
        {stare.x+1,stare.y-1},{stare.x+1,stare.y},{stare.x+1,stare.y+1}
    };

    std::vector<Organizm*> doUsuniecia;
    for (int i = 0; i < 8; i++) {
        if (!swiat->czyNaMapie(sasiedzi[i])) continue;
        Organizm* org = swiat->getOrganizmAt(sasiedzi[i]);
        if (org == nullptr) continue;
        if (org->getTypOrganizmu() == ZWIERZE && dynamic_cast<Cyberowca*>(org) == nullptr) {
            doUsuniecia.push_back(org);
        }
    }
    for (Organizm* org : doUsuniecia) {
        swiat->dodajKomunikat("Barszcz Sosnowskiego zabil " + std::string(1, org->GetSymbol()) + "!");
        swiat->usunOrganizm(org);
    }
    rozrost();
}

void BarszczSosnowskiego::kolizja(Organizm* atakujacy) {
    if (atakujacy == nullptr) return;

    if (dynamic_cast<Cyberowca*>(atakujacy) != nullptr) {
        swiat->dodajKomunikat("Cyberowca zjadla Barszcz Sosnowskiego!");
        swiat->usunOrganizm(this);
    } else {
        swiat->dodajKomunikat("Barszcz Sosnowskiego: " +
            std::string(1, atakujacy->GetSymbol()) + " zginal!");
        swiat->usunOrganizm(atakujacy);
        swiat->usunOrganizm(this);
    }
}