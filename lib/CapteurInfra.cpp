#include "CapteurInfra.hpp"

const uint8_t NUM_PORTA_ENTREE_ANALOGIQUE = 2;
const uint8_t VALEUR_ADC_MIN = 150;

CapteurInfra::CapteurInfra() : nPersonnes_(0), voltage_(0), objetDetecte_(false)
{
}

void CapteurInfra::lireVoltage() 
{
    voltage_ = convertisseur.lecture(NUM_PORTA_ENTREE_ANALOGIQUE);
    objetDetecte_ = (voltage_ > VALEUR_ADC_MIN);
}

bool CapteurInfra::estObjetDetecte() 
{
    return objetDetecte_;
}