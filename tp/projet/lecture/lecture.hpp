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

enum Instruction {
    DEBUT = 0b00000001,
    PLACE_DE_STATIONNEMENT = 0b00000010, 
    NOTE_JOUEE = 0b01001000, 
    PARCOURS_SENS_HORAIRE = 0b01100100,
    PARCOURS_SENS_ANTIHORAIRE = 0b01100101, 
    FIN = 0b11111111
};

class Lecture
{
public:
    Lecture();    
    void initialiserLecture();
    void selectionMode();
    void lireMemoire();
    void faireInstruction(uint8_t instruction, uint8_t operande);
    

    uint16_t adresse_;
    uint8_t donnee_;
    uint8_t instruction_;
    uint8_t operande_;

    uint16_t adresseBoucle_;
    uint8_t compteurBoucle_;

    Del del_;
    Memoire24CXXX mem_;
    Communication com_;

    bool programmeFini_;
};