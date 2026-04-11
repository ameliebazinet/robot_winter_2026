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

bool CapteurLigne::estObstacleAuCentre() const
{
    if (estSurLignePleine())
        return false;
    else
        return estTropAGaucheLarge() || estTropADroiteLarge() || (lireTousCapteurs() & CAPTEUR_D3);
}

bool CapteurLigne::estSurLignePleine() const
{
    return (lireTousCapteurs() == TOUS_LES_CAPTEURS);
}

bool CapteurLigne::estVide() const
{
    return (lireTousCapteurs() == 0);
}

bool CapteurLigne::estAllumeCapteurQuelconque() const
{
    return (lireTousCapteurs());
}