#define DEBUG 
#include "lecture.hpp"
#include "debug.h"

const uint16_t DELAI_2_SECONDES = 2000;
const uint8_t DELAI_1_SECONDE = 1000;
const uint8_t DELAI_INTERRUPTION = 50;

Lecture::Lecture() : adresse_(0x0000), donnee_(0), instruction_(0b00), 
    operande_(0b00), adresseBoucle_(0), del_(PORTA, PA0, PA1), programmeFini_(false)
{
    PontH::initialiserRegistre();
    Son::initialiserPiezo();
}

void Lecture::selectionMode(volatile bool& boutonClique, volatile bool& tempsEcoule)
{
    InterruptionExterne boutonMateriel;
    _delay_ms(DELAI_2_SECONDES);

    // INT0 sur any logical change
    boutonMateriel.initialisation(0,1);

    bool modeChoisi = false;

    del_.allumerCouleur(Del::Couleur::VERT);
    Minuterie::Minuterie1::partirMinuterie(DELAI_2_SECONDES, Minuterie::Comparateur::A);

    while (!boutonClique && !tempsEcoule) {
        // Attente active
    }

        if (boutonClique) {
            Minuterie::Minuterie1::desactiverInteruptionComparateurA();
            
            // LOGIQUE : SET AU MODE RAPPORT
            modeChoisi = true;
        } 
        else if (tempsEcoule) {
            del_.allumerCouleur(Del::Couleur::ETEINT);
            _delay_ms(DELAI_1_SECONDE);
        }

    boutonClique = false;
    tempsEcoule = false;
    
    del_.allumerCouleur(Del::Couleur::ROUGE);
    Minuterie::Minuterie1::partirMinuterie(DELAI_2_SECONDES, Minuterie::Comparateur::A);

    while (!boutonClique && !tempsEcoule) {
        // Attente active
    }

    if (boutonClique) {
        Minuterie::Minuterie1::desactiverInteruptionComparateurA();
        
        // LOGIQUE : SET AU MODE RAPPORT
        modeChoisi = true;
    } 
    else if (tempsEcoule) {
        del_.allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(DELAI_1_SECONDE);
    }

    boutonMateriel.desactiverInterruption(0);
}


void Lecture::initialiserLecture()
{
    com_.initialisationUART();
}

void Lecture::faireInstruction(uint8_t instruction, uint8_t operande)
{
    switch (instruction) {
        case PLACE_DE_STATIONNEMENT:
            break;
        
        case NOTE_JOUEE:
            break;

        case PARCOURS_SENS_HORAIRE:
            break;

        case PARCOURS_SENS_ANTIHORAIRE:
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





