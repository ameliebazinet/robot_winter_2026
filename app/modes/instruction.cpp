// Fichier : instruction.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation du mode instruction.
// Lit les paramètres depuis l'EEPROM et affiche les informations de configuration du robot.

#include "instruction.hpp"


void faireInstruction(Lecture& lecture)
{
    Son::initialiserPiezo();
   
    for (uint8_t i = 0; i < 8; i++)
    {
        lecture.getDel().allumerCouleur(Del::Couleur::VERT);
        _delay_ms(125);
        lecture.getDel().allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(125);
    }
    
    ecrireDepuisUART();
    _delay_ms(10); 
    lecture.lireMemoire();

    for (uint8_t i = 0; i < 3; i++)
    {
        Son::jouer(lecture.getNote()[i]);
        _delay_ms(250);
        Son::arreter();
        _delay_ms(125);
    }

    _delay_ms(DELAI_2_SECONDES);

    if (lecture.getDirectionHoraire())
    {
        lecture.getDel().allumerCouleur(Del::Couleur::VERT);
        _delay_ms(DELAI_2_SECONDES);
    }
    else
    {
        lecture.getDel().allumerCouleur(Del::Couleur::ROUGE);
        _delay_ms(DELAI_2_SECONDES);
    }
    lecture.getDel().allumerCouleur(Del::Couleur::ETEINT);
    _delay_ms(DELAI_2_SECONDES);
    for (uint8_t i = 0; i < lecture.getNumStationnement(); i++)
    {
       
        lecture.getDel().allumerCouleurAmbre();
        _delay_ms(DELAI_CLIGNOTEMENT_AMBRE);
        lecture.getDel().allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(DELAI_CLIGNOTEMENT_AMBRE);
    }
    lecture.getDel().allumerCouleur(Del::Couleur::ETEINT);
}