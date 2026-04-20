// Fichier : CapteurLigne.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation du capteur de ligne pour le suivi de trajectoire.
// Gère la lecture des 5 capteurs de ligne et la détection de la position du robot.

#include "CapteurLigne.hpp"

CapteurLigne::CapteurLigne()
{
    DDRA &= ~(TOUS_LES_CAPTEURS);
}

uint8_t CapteurLigne::lireTousCapteurs() const
{
    return (TOUS_LES_CAPTEURS & PINA);
}

bool CapteurLigne::estTropAGaucheLarge() const
{
    return (CAPTEUR_D1 & PINA) && (CAPTEUR_D2 & PINA);
}

bool CapteurLigne::estAllumeD2() const
{
    return (CAPTEUR_D2 & PINA);
}

bool CapteurLigne::estAllumeD4() const
{
    return (CAPTEUR_D4 & PINA);
}

bool CapteurLigne::estTropADroiteLarge() const
{
    return (CAPTEUR_D5 & PINA) && (CAPTEUR_D4 & PINA);
}

bool CapteurLigne::estTropADroite() const
{
    return (CAPTEUR_D5 & PINA);
}

bool CapteurLigne::estTropAGauche() const
{
    return (CAPTEUR_D1 & PINA);
}

bool CapteurLigne::estTropPresMur() const
{
    return ( (PINA & CAPTEUR_D4) && (PINA & CAPTEUR_D5) );
}

// bool CapteurLigne::estObstacleAuCentre() const
// {
//     if (estSurLignePleine())
//         return false;
//     else
//         return (estAllumeMilieu() || (estAllumeD4() && estTropAGauche()) || 
//         (estAllumeD2() && estTropADroite()) || (estTropADroite() && estTropAGauche()));
// }

bool CapteurLigne::estObstacleAuCentre() const
{
    if (estSurLignePleine()) return false;

    bool d1 = (CAPTEUR_D1 & PINA);
    bool d2 = (CAPTEUR_D2 & PINA);
    bool d3 = (CAPTEUR_D3 & PINA);
    bool d4 = (CAPTEUR_D4 & PINA);
    bool d5 = (CAPTEUR_D5 & PINA);

    if (d3) return true;                        // D3 allumé = obstacle au centre
    if (d4 && (!d5 || d1)) return true;         // D4 actif, sauf D4+D5 seuls (trop près mur droit)
    if (d2 && !d4 && (!d1 || d5)) return true;  // D2 actif, sauf D1+D2 seuls (trop près mur gauche)
    if (d5 && d1 && !d4 && !d2) return true;    // D5+D1 seuls (obstacle aux extrémités)

    return false;
}

bool CapteurLigne::estSurLignePleine() const
{
    return (lireTousCapteurs() == TOUS_LES_CAPTEURS);
}

bool CapteurLigne::estVide() const
{
    return (lireTousCapteurs() == 0);
}

bool CapteurLigne::estAllumeMilieu() const
{
    return(PINA & CAPTEUR_D3 ); 
}

bool CapteurLigne::estAllumeCapteurQuelconque() const
{
    return (lireTousCapteurs());
}

bool CapteurLigne::estTroisCapteursActifs() const
{
    uint8_t count = ((CAPTEUR_D1 & PINA) ? 1 : 0)
                  + ((CAPTEUR_D2 & PINA) ? 1 : 0)
                  + ((CAPTEUR_D3 & PINA) ? 1 : 0)
                  + ((CAPTEUR_D4 & PINA) ? 1 : 0)
                  + ((CAPTEUR_D5 & PINA) ? 1 : 0);
    return count >= 3;
}