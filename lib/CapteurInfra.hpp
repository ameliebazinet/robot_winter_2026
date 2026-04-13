#include <avr/io.h>
#include "can.h"

class CapteurInfra
{
public:
    CapteurInfra();
    void lireVoltage();
    bool estObjetDetecte();
    can can;
    uint8_t nPersonnes_;

private:
    uint16_t voltage_;
    bool objetDetecte_;
};