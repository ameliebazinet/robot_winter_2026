#pragma once
#define F_CPU 8000000UL
#include <util/delay.h>
#include "Communication.hpp"
#include "memoire_24.h"
#include "Del.hpp"
#include "PontH.hpp"
#include "Son.hpp"
#include "InterruptionExterne.hpp"
#include "Minuterie.hpp"

constexpr uint8_t ADRESSE_TAILLE = 2;
const uint8_t TAILLE_TABLEAU_NOTE = 3; 

enum Instruction {
    DEBUT = 0b00000001,
    PLACE_DE_STATIONNEMENT = 0b00000010, 
    NOTE_JOUEE = 0b01001000, 
    PARCOURS_SENS_HORAIRE = 0b01100100,
    PARCOURS_SENS_ANTIHORAIRE = 0b01100101, 
    FIN = 0b11111111
};

enum Mode {
    SELECTION, 
    INSTRUCTION, 
    RAPPORT, 
    EXECUTION
}; 

class Lecture
{
public:
    Lecture();    
    Mode selectionMode(volatile bool& boutonClique, volatile bool& tempsEcoule);
    void implementationMode(const Mode& mode);
    void initialiserLecture();
    void lireMemoire();
    void faireInstruction(uint8_t instruction, uint8_t operande);
 

    

    uint16_t adresse_;
    uint8_t donnee_;
    uint8_t instruction_;
    uint8_t operande_;
    
    
    uint8_t note_[TAILLE_TABLEAU_NOTE];
    bool directionHoraire_; 
    uint8_t valeurAtt_;

    bool programmeFini_; 

    uint8_t adresseTableauNote = 0;

    Del del_;
    Memoire24CXXX mem_;
    Communication com_;
};