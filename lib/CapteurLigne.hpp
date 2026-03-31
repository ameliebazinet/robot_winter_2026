#pragma once
#include <avr/io.h>
#include <stdint.h>

class CapteurLigne
{
public:
    CapteurLigne();
    uint8_t lireTousCapteurs() const;

    bool estTropAGauche() const;
    bool estTropADroite() const;
    bool estObstacleAuCentre() const;
    bool estSurLignePleine() const;

private:
    static const uint8_t CAPTEUR_D1 = (1 << PC0);
    static const uint8_t CAPTEUR_D2 = (1 << PC1);
    static const uint8_t CAPTEUR_D3 = (1 << PC2);
    static const uint8_t CAPTEUR_D4 = (1 << PC3);
    static const uint8_t CAPTEUR_D5 = (1 << PC4);
    static const uint8_t TOUS_LES_CAPTEURS = (CAPTEUR_D1 | CAPTEUR_D2 | CAPTEUR_D3 | CAPTEUR_D4 | CAPTEUR_D5);
};