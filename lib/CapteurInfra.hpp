#include <avr/io.h>
#include "can.h"

class CapteurInfra
{
public:
    CapteurInfra();
    void lireVoltage();
    bool estObjetDetecte();
    can convertisseur;
    uint8_t nPersonnes_;
    uint16_t getVoltage() {return voltage_;}

private:
    uint16_t voltage_;
    bool objetDetecte_;
};