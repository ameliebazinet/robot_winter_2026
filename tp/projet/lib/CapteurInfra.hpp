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
    
    can can1;

    uint16_t voltage;
    uint8_t distance;
    bool detecteObjet;
};