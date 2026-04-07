#include "CapteurLigne.hpp"

CapteurLigne::CapteurLigne()
{
    DDRC &= ~(TOUS_LES_CAPTEURS);
}

uint8_t CapteurLigne::lireTousCapteurs() const
{
    return (TOUS_LES_CAPTEURS & PINA);
}

bool CapteurLigne::estTropAGauche() const
{
    return (CAPTEUR_D1 & PINA) && (CAPTEUR_D2 & PINA);
}

bool CapteurLigne::estTropADroite() const
{
    return (CAPTEUR_D5 & PINA) && (CAPTEUR_D4 & PINA);
}

bool CapteurLigne::estTropADroitePrecis() const
{
    return (CAPTEUR_D5 & PINA);
}

bool CapteurLigne::estTropAGauchePrecis() const
{
    return (CAPTEUR_D1 & PINA);
}

bool CapteurLigne::estTropPresMur() const
{
    return ( (PINA & CAPTEUR_D4) && (PINA & CAPTEUR_D5) );
}

bool CapteurLigne::estObstacleAuCentre() const
{
    return ((CAPTEUR_D3 & PINA) || ((CAPTEUR_D2 | CAPTEUR_D3) & PINA) || ((CAPTEUR_D3 | CAPTEUR_D4) & PINA));
}

bool CapteurLigne::estSurLignePleine() const
{
    return (lireTousCapteurs() == TOUS_LES_CAPTEURS);
}

bool CapteurLigne::estVide() const
{
    return (lireTousCapteurs() == !(TOUS_LES_CAPTEURS));
}

