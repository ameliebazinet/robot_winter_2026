// Test pour vérifier si le code de track des lignes marche.

#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>


int main()
{
    CapteurLigne capteur;
    PontH::initialiserRegistre();

    PontH::reculer(175);
    _delay_ms(3000);
    PontH::arreter();
}
