// Fichier : CapteurInfra.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation du capteur infrarouge pour la détection d'obstacles.
// Gère la lecture des capteurs IR et l'interprétation des distances mesurées.

#include "CapteurInfra.hpp"

const uint8_t NUM_PORTA_ENTREE_ANALOGIQUE = 2;
const uint8_t VALEUR_ADC_MIN = 120;

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