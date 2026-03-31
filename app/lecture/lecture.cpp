#define DEBUG 
#include "lecture.hpp"
#include "debug.h"
#include "../modes/execution.hpp"
#include "../modes/instruction.hpp"
#include "../modes/rapport.hpp"

const uint16_t DELAI_2_SECONDES = 2000;
const uint16_t DELAI_1_SECONDE = 1000;
const uint8_t DELAI_INTERRUPTION = 50;
const uint16_t DELAI_CLIGNOTEMENT_AMBRE= 500;

Lecture::Lecture() : adresse_(0x0000), donnee_(0), instruction_(0b00), 
    operande_(0b00), del_(PORTA, PA0, PA1), programmeFini_(false)
{
    PontH::initialiserRegistre();
    Son::initialiserPiezo();
}



void Lecture::demarrerPhase(Del::Couleur couleur, uint16_t delai)
{
    del_.allumerCouleur(couleur); 
    Minuterie::Minuterie1::partirMinuterie(DELAI_2_SECONDES, Minuterie::Comparateur::A);
}

void Lecture::attendreEvenement(volatile bool& boutonClique, volatile bool& tempsEcoule)
{
        while (!boutonClique && !tempsEcoule) {
        // Attente active
    }
}

void Lecture::attendreEntrePhase(volatile bool& boutonClique, volatile bool& tempsEcoule)
{
    boutonClique = false; 
    tempsEcoule = false; 
    del_.allumerCouleur(Del::Couleur::ETEINT);
    _delay_ms(DELAI_1_SECONDE); 
}

Mode Lecture::confirmerMode(InterruptionExterne& boutonMateriel, Mode mode)
{
    Minuterie::Minuterie1::desactiverInteruptionComparateurA();
    boutonMateriel.desactiverInterruption(0); // selection de mode est fait, on ne veux plus qui aille des intéruptions sur le bouton 
    del_.allumerCouleur(Del::Couleur::ETEINT);
    return Mode::INSTRUCTION; 
}



Mode Lecture::selectionnerMode(volatile bool& boutonClique, volatile bool& tempsEcoule)
{
    InterruptionExterne boutonMateriel;
    // INT0 sur any logical change
    boutonMateriel.initialisation(0,1);

    // Phase verte. 
    demarrerPhase(Del::Couleur::VERT, DELAI_2_SECONDES); 
    attendreEvenement(boutonClique,tempsEcoule); 
    if(boutonClique)
        return confirmerMode(boutonMateriel,Mode::INSTRUCTION);

    // pause
    attendreEntrePhase(boutonClique,tempsEcoule); 

    // Phase rouge. 
    demarrerPhase(Del::Couleur::ROUGE, DELAI_2_SECONDES); 
    attendreEvenement(boutonClique,tempsEcoule); 
    if(boutonClique) 
        return confirmerMode(boutonMateriel,Mode::RAPPORT);
    
    boutonClique = false; 
    tempsEcoule = false; 
    boutonMateriel.desactiverInterruption(0); 
    del_.allumerCouleur(Del::Couleur::ETEINT); 
    _delay_ms(DELAI_1_SECONDE);
    return Mode::EXECUTION;

}


void Lecture::initialiserLecture()
{
    com_.initialisationUART();
}

void Lecture::faireInstruction(uint8_t instruction, uint8_t operande)
{
    switch (instruction) {
        case PLACE_DE_STATIONNEMENT:
            valeurAtt_ = operande;
            break;
        
        case NOTE_JOUEE:
            note_[adresseTableauNote] = operande;
            adresseTableauNote++;
            break;

        case PARCOURS_SENS_HORAIRE:
            directionHoraire_ = true;
            break;

        case PARCOURS_SENS_ANTIHORAIRE:
            directionHoraire_ = false;
            break;

        case FIN:
            programmeFini_ = true;    
            break;
    }
}

void Lecture::lireMemoire()
{
    mem_.lecture(adresse_++, &donnee_);
    uint16_t taille = donnee_;
    mem_.lecture(adresse_++, &donnee_);
    taille = (taille << 8) | donnee_;

    bool estDebutTrouve = false;

    while (adresse_ < taille && !programmeFini_) {
        mem_.lecture(adresse_++, &instruction_);
        mem_.lecture(adresse_++, &operande_);

        if (instruction_ == DEBUT) {
            break;
        }
    }

    while (adresse_ < taille && !programmeFini_) {
        mem_.lecture(adresse_++, &instruction_);
        mem_.lecture(adresse_++, &operande_);

        faireInstruction(instruction_, operande_);
    }
}





