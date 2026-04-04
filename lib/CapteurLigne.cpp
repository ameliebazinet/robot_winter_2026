#include "CapteurLigne.hpp"

CapteurLigne::CapteurLigne()
{
    DDRC &= ~(TOUS_LES_CAPTEURS);
}

uint8_t CapteurLigne::lireTousCapteurs() const
{
    return (TOUS_LES_CAPTEURS & PINC);
}

bool CapteurLigne::estTropAGauche() const
{
    return (CAPTEUR_D1 & PINC);
}

bool CapteurLigne::estTropADroite() const
{
    return (CAPTEUR_D5 & PINC);
}

bool CapteurLigne::estTropPresMur() const
{
    return ( (PINC & CAPTEUR_D4) && (PINC & CAPTEUR_D5) );
}

bool CapteurLigne::estObstacleAuCentre() const
{
    return ((CAPTEUR_D3 & PINC) || ((CAPTEUR_D2 | CAPTEUR_D3) & PINC) || ((CAPTEUR_D3 | CAPTEUR_D4) & PINC));
}

bool CapteurLigne::estSurLignePleine() const
{
    return (lireTousCapteurs() == TOUS_LES_CAPTEURS);
}
