// Test pour vérifier si le code de track des lignes marche.

#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>


int main()
{
    CapteurLigne capteur;
    PontH::initialiserRegistre();
    uint8_t nObstacles = 0;
    bool estSurObstacleAvant = false;    

    PontH::avancer(255);
    _delay_ms(100);

    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = false;
        if (estSurObstacleMaintenant && !estSurObstacleAvant)
            nObstacles++;
        estSurObstacleAvant = estSurObstacleMaintenant;

        if (capteur.estTropADroite())
            PontH::configurer(1, 175, 0, 175);
        else if (capteur.estTropAGauche())
            PontH::configurer(0, 175, 1, 175);
        else
            PontH::avancer(100);
    }

    PontH::arreter();
}
