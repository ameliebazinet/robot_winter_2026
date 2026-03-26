#define DEBUG 
#include "lecture.hpp"
#include "debug.h"

Lecture::Lecture() 
    : adresse_(0x0000), donnee_(0), instruction_(0b00), 
    operande_(0b00), adresseBoucle_(0), del_(PORTA, PA0, PA1),
    programmeFini_(false)
{
    PontH::initialiserRegistre();
    Son::initialiserPiezo();
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





