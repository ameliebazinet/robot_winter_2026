#include "CapteurInfra.hpp"

const uint8_t NUM_PORTA_ENTREE_ANALOGIQUE = 0;
const uint8_t DISTANCE_MAXIMAL_CM = 40;

CapteurInfra::CapteurInfra() : voltage_(0), distance_(0), objetDetecte_(false) {}



void CapteurInfra::lireVoltage() {
    uint16_t adcValeur = can1.lecture(NUM_PORTA_ENTREE_ANALOGIQUE);
    
    voltage_ = adcValeur;//(adcValeur / 1023.0) * 5.0;
}
uint16_t CapteurInfra::getVoltage(){
    return voltage_;
}
uint8_t CapteurInfra::getDistance(){
    return distance_;
}

bool CapteurInfra::estObjetDetecte(){
    return objetDetecte_;
}
void CapteurInfra::lireDistance() {
    lireVoltage();  
    
    // Convertir ADC en voltage 
    float volts = (voltage_ / 1023.0f) * 5.0f;
        // Formule trouvée sur internet pour calculer distance ajustée a notre capteur 
    // if (volts > 0.4f)
    distance_ = (uint8_t)(27.86f / volts - 0.42f);  
    // else
    //     distance = 255;  // hors portée
    
    objetDetecte_ = distance_ < DISTANCE_MAXIMAL_CM;
}