#include "CapteurInfra.hpp"

const uint8_t NUM_PORTA_ENTREE_ANALOGIQUE = 2;
const uint8_t VALEUR_ADC_MIN = 120;

CapteurInfra::CapteurInfra() : voltage_(0), distance_(0), objetDetecte_(false), estUnePersonne_(false), nPersonnes_(0) {
    resetEstUnePersonne();
}

uint16_t CapteurInfra::getValeurADC()
{
    return can1.lecture(NUM_PORTA_ENTREE_ANALOGIQUE);
}

void CapteurInfra::lireVoltage() {
    voltage_ = can1.lecture(NUM_PORTA_ENTREE_ANALOGIQUE);
    objetDetecte_ = (voltage_ > VALEUR_ADC_MIN);
}

uint16_t CapteurInfra::getVoltage(){
    return voltage_;
}
uint8_t CapteurInfra::getDistance(){
    return distance_;
}
uint8_t CapteurInfra::getnPersonnes(){
    return nPersonnes_;
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
    if (volts < 0.1f) {  // capteur hors portée ou débranché
        objetDetecte_ = false;
        distance_ = 255;
        return;
    }

    distance_ = (uint8_t)(29.988f * pow(volts, -1.173f));
  
    // else
    //     distance = 255;  // hors portée
    
    objetDetecte_ = distance_ < VALEUR_ADC_MIN;
}

void CapteurInfra::incrementerPersonne(){
    if(objetDetecte_ && estUnePersonne_){
        nPersonnes_++;
        estUnePersonne_ = false;
    }
    else if (!objetDetecte_){
        estUnePersonne_ = true;
    }
}

void CapteurInfra::resetEstUnePersonne(){
    estUnePersonne_ = true;
}
