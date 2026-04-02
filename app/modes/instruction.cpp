#include "instruction.hpp"

void faireInstruction()
{
    Lecture lecture;

    // signalement du début
    for (uint8_t i = 0; i < 8; i++)
    {
        lecture.getDel().allumerCouleur(Del::Couleur::VERT);
        _delay_ms(125);
        lecture.getDel().allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(125);
    }
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
        // allumer vert
        lecture.getDel().allumerCouleur(Del::Couleur::VERT);
        _delay_ms(DELAI_2_SECONDES);
    }
    else
    {
        lecture.getDel().allumerCouleur(Del::Couleur::ROUGE);
        _delay_ms(DELAI_2_SECONDES);
    }

    _delay_ms(DELAI_2_SECONDES);

    // allumer la del ambre :
    for (uint8_t i = 0; i < lecture.getNumStationnement(); i++)
    {
        lecture.getDel().allumerCouleurAmbre();
        _delay_ms(DELAI_CLIGNOTEMENT_AMBRE);
        lecture.getDel().allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(DELAI_CLIGNOTEMENT_AMBRE);
    }
}