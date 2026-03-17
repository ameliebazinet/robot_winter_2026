#include "Communication.hpp"
#include "memoire_24.h"

constexpr uint8_t ADRESSE_TAILLE = 2;

int main()
{
    Communication com;
    Memoire24CXXX mem;
    com.initialisationUART();

    uint16_t adresse = 0x0000;
    uint8_t val = 0;
    uint16_t taille = mem.lecture(adresse, (uint8_t*)&val, ADRESSE_TAILLE); // uint8_t taille mem.lecture qu'on refait 2 fois (un octet a la fois). Après il faut bitshift (mem.lecture(0) << 8 | mem.lecture(1))
    adresse = adresse + ADRESSE_TAILLE;

    for (uint8_t i = 0; i < taille; i++ ) {
        mem.lecture(adresse, &val);
        adresse++;
    }
    
    // SWITCH CASE : CHAQUE INSTRUCTION CODER QUOI FAIRE

    return 1;
}