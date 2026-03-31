// Test pour vérifier si le code de track des lignes marche.

#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>


int main()
{
    CapteurLigne capteur;
    PontH::initialiserRegistre();

    PontH::avancer(255);
    _delay_ms(100);

    while (!capteur.estSurLignePleine()) {

        if (capteur.estTropADroite()) {
            PontH::configurer(1, 100, 0, 100);
        }

        else if (capteur.estTropAGauche()) {
            PontH::configurer(0, 100, 1, 100);
        }

        else {
            PontH::avancer(100);
        }
    }
    PontH::arreter();
}
