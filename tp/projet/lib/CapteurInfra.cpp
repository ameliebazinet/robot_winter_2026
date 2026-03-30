#include "CapteurInfra.hpp"

const uint8_t NUM_PORTA_ENTREE_ANALOGIQUE = 0;
const uint8_t DISTANCE_MAXIMAL_CM = 80;

CapteurInfra::CapteurInfra() : voltage(0), distance(0), detecteObjet(false) {}



void CapteurInfra::lireVoltage() {
    uint16_t adcValeur = can1.lecture(NUM_PORTA_ENTREE_ANALOGIQUE);
    
    voltage = adcValeur;//(adcValeur / 1023.0) * 5.0;
}
void CapteurInfra::lireDistance() {
    distance = 0;
    detecteObjet = distance < DISTANCE_MAXIMAL_CM;
}