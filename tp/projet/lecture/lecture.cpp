#define DEBUG 
#include "lecture.hpp"
#include "debug.h"

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

Mode Lecture::selectionMode(volatile bool& boutonClique, volatile bool& tempsEcoule)
{
    InterruptionExterne boutonMateriel;
    _delay_ms(DELAI_2_SECONDES);

    // INT0 sur any logical change
    boutonMateriel.initialisation(0,1);

    //bool modeChoisi = false;

    del_.allumerCouleur(Del::Couleur::VERT);
    Minuterie::Minuterie1::partirMinuterie(DELAI_2_SECONDES, Minuterie::Comparateur::A);

    while (!boutonClique && !tempsEcoule) {
        // Attente active
    }

        if (boutonClique) {
            Minuterie::Minuterie1::desactiverInteruptionComparateurA();
            boutonMateriel.desactiverInterruption(0); // selection de mode est fait, on ne veux plus qui aille des intéruptions sur le bouton 
            del_.allumerCouleur(Del::Couleur::ETEINT);
            return Mode::INSTRUCTION; 
            
        } 
        
        // le temps est écoulée, il n'a pas eu d'intéruption. 
        // pause, la del est etteinte
        boutonClique = false; 
        tempsEcoule = false; 
        del_.allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(DELAI_1_SECONDE); 

        // phase rouge
        del_.allumerCouleur(Del::Couleur::ROUGE); 
        Minuterie::Minuterie1::partirMinuterie(DELAI_2_SECONDES, Minuterie::Comparateur::A);
        
        
        while (!boutonClique && !tempsEcoule) {
        // Attente active
    }

        if (boutonClique) {
            Minuterie::Minuterie1::desactiverInteruptionComparateurA();
            boutonMateriel.desactiverInterruption(0); // selection de mode est fait, on ne veux plus qui aille des intéruptions sur le bouton 
            del_.allumerCouleur(Del::Couleur::ETEINT);
            return Mode::RAPPORT; 
        }
        // LA SÉQUENCE C'EST COMPLÉTER SANS INTERRUPTION : 
        boutonClique = false; 
        tempsEcoule = false; 
        boutonMateriel.desactiverInterruption(0); 
        del_.allumerCouleur(Del::Couleur::ETEINT); 
        _delay_ms(DELAI_1_SECONDE);
        return Mode::EXECUTION;
}

void Lecture::implementationMode(const Mode& mode)
{
    switch (mode) {
        case Mode::INSTRUCTION:
            // siganlement du début 
            for (uint8_t i = 0; i < 8; i++)
            {
                del_.allumerCouleur(Del::Couleur::VERT); 
                _delay_ms(125); 
                del_.allumerCouleur(Del::Couleur::ETEINT); 
                _delay_ms(125); 
            }
            lireMemoire(); 
            for(uint8_t i = 0; i < 3; i++) {
                Son::jouer(note_[i]);
                _delay_ms(250); 
                Son::arreter();
                _delay_ms(125); 
            }

            _delay_ms(DELAI_2_SECONDES); 
            if(directionHoraire_){
                // allumer vert
                del_.allumerCouleur(Del::Couleur::VERT); 
                _delay_ms(DELAI_2_SECONDES); 
            }
            else {
                del_.allumerCouleur(Del::Couleur::ROUGE); 
                _delay_ms(DELAI_2_SECONDES); 
            }

            _delay_ms(DELAI_2_SECONDES);

            // allumer la del ambre : 

            for(uint8_t i = 0; i < valeurAtt_; i++)
            {
                del_.allumerCouleurAmbre(); 
                _delay_ms(DELAI_CLIGNOTEMENT_AMBRE); 
                del_.allumerCouleur(Del::Couleur::ETEINT); 
                _delay_ms(DELAI_CLIGNOTEMENT_AMBRE); 
            }

            break;
        
        case RAPPORT:


            break;

        case EXECUTION:
            break;

    }
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
            // call une fonction jouerSerieNotes(adresse) qu'on implemente ailleurs
            
            break;

        case PARCOURS_SENS_HORAIRE:
            directionHoraire_ = true;
            break;

        case PARCOURS_SENS_ANTIHORAIRE:
            directionHoraire_ = false;
            break;

        case FIN:
            // call une fonction effectuerProgramme() qu'on implemente ailleurs
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





