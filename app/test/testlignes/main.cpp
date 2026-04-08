// Test pour vérifier si le code de track des lignes marche.

#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>
#include "Del.hpp"

int main()
{
    CapteurLigne capteur;
    Del del(PORTA, PA2, PA3);
    PontH::initialiserRegistre();

    uint8_t nObstacles = 0;
    bool estSurObstacleAvant = false;    

    PontH::avancer(255);
    _delay_ms(100);

    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = capteur.estObstacleAuCentre();
        
        if (estSurObstacleMaintenant && !estSurObstacleAvant)
            nObstacles++;

        if (estSurObstacleMaintenant)
            del.allumerCouleur(Del::Couleur::ROUGE);
        else
            del.allumerCouleur(Del::Couleur::ETEINT);

        estSurObstacleAvant = estSurObstacleMaintenant;

        if (capteur.estActiveD4D5())
            PontH::configurer(1, 175, 0, 175);
        else if (capteur.estActiveD1D2())
            PontH::configurer(0, 175, 1, 175);
        else
            PontH::avancer(100);
    }
    del.allumerCouleur(Del::Couleur::ETEINT);
    PontH::arreter();
}