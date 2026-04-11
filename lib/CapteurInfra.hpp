#include <avr/io.h>
#include "can.h"
#include <math.h>

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
    void incrementerPersonne();
    can can1;
    uint8_t getnPersonnes();
    void resetEstUnePersonne();
    uint8_t nPersonnes_;

private:
    uint16_t voltage_;
    uint8_t distance_;
    bool objetDetecte_;
    bool estUnePersonne_;
};