#include <avr/io.h>
#include "can.h"

class CapteurInfra
{
public:
    CapteurInfra();
    // Lit le voltage produit par le capteur infra avec Can
    void lireVoltage();
    // Converti le voltage en distance
    void lireDistance();
    uint16_t getVoltage();
    uint8_t getDistance();
    bool estObjetDetecte();
    can can1;

    uint16_t voltage;
    uint8_t distance;
    bool objetDetecte;
};