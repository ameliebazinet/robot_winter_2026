#define F_CPU 8000000UL
#include <util/delay.h>
#include "PontH.hpp"
#include "Del.hpp"

int main()
{

    PontH::initialiserRegistre();

    // Test avancer
    PontH::avancer(75);
    _delay_ms(2000);

    // Test reculer
    PontH::reculer(75);
    _delay_ms(2000);

    // Test tourner droite
    PontH::tournerDroite(50);
    _delay_ms(2000);

    // Test tourner gauche
    PontH::tournerGauche(50);
    _delay_ms(2000);

    // Test configurer (direction et ratio custom)
    PontH::configurer(0, 30, 1, 60);
    _delay_ms(2000);

    // Test arreter
    PontH::arreter();

    while (true) {}
}