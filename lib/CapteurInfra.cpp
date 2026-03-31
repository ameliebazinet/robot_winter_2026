#include "CapteurInfra.hpp"

const uint8_t NUM_PORTA_ENTREE_ANALOGIQUE = 0;
const uint8_t DISTANCE_MAXIMAL_CM = 200;

CapteurInfra::CapteurInfra() : voltage(0), distance(0), objetDetecte(false) {}



void CapteurInfra::lireVoltage() {
    uint16_t adcValeur = can1.lecture(NUM_PORTA_ENTREE_ANALOGIQUE);
    
    voltage = adcValeur;//(adcValeur / 1023.0) * 5.0;
}
// void CapteurInfra::lireDistance() {
//     distance = 0;
//     detecteObjet = distance < DISTANCE_MAXIMAL_CM;
// }

void CapteurInfra::lireDistance() {
    lireVoltage();  
    
    // Convertir ADC en voltage 
    float volts = (voltage / 1023.0f) * 5.0f;
    
    // Formule trouvée sur internet pour calculer distance ajustée a notre capteur 
    // if (volts > 0.4f)
    distance = (uint8_t)(27.86f / volts - 0.42f);  
    // else
    //     distance = 255;  // hors portée
    
    objetDetecte = distance < DISTANCE_MAXIMAL_CM;
}