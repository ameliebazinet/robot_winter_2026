#pragma once
#include <avr/io.h>
#include <stdint.h>

class CapteurLigne
{
public:
    CapteurLigne();
    uint8_t lireTousCapteurs() const;

    bool estTropAGaucheLarge() const;
    bool estAllumeD2() const;
    bool estAllumeD4() const;
    bool estTropAGauche() const;
    bool estTropADroite() const;
    bool estTropADroiteLarge() const;
    bool estTropPresMur() const;
    bool estObstacleAuCentre() const;
    bool estSurLignePleine() const;
    bool estVide() const;
    bool estAllumeCapteurQuelconque() const;
    bool estAllumeMilieu() const;
    bool estTroisCapteursActifs() const;

private:
    static const uint8_t CAPTEUR_D1 = (1 << PA0);
    static const uint8_t CAPTEUR_D2 = (1 << PA1);
    static const uint8_t CAPTEUR_D3 = (1 << PA3);
    static const uint8_t CAPTEUR_D4 = (1 << PA4);
    static const uint8_t CAPTEUR_D5 = (1 << PA6);
    static const uint8_t TOUS_LES_CAPTEURS = (CAPTEUR_D1 | CAPTEUR_D2 | CAPTEUR_D3 | CAPTEUR_D4 | CAPTEUR_D5);
};