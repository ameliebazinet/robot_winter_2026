#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PontH.hpp"

int main()
{
    PontH::initialiserRegistre();

    while (true) {
        PontH::avancer(75);
        _delay_ms(2000);

        PontH::arreter();
        _delay_ms(500);

        PontH::reculer(75);
        _delay_ms(2000);

        PontH::arreter();
        _delay_ms(500);

        PontH::tournerDroite(75);
        _delay_ms(1000);

        PontH::arreter();
        _delay_ms(500);

        PontH::tournerGauche(75);
        _delay_ms(1000);

        PontH::arreter();
        _delay_ms(500);
    }

    return 0;
}