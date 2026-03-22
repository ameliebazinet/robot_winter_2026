#define F_CPU 8000000UL
#include <util/delay.h>
#include "Communication.hpp"
#include "memoire_24.h"
#include "Del.hpp"
#include "PontH.hpp"

// INCLUDE SON

constexpr uint8_t ADRESSE_TAILLE = 2;

enum Instruction {
    DEBUT = 0b00000001,
    ATTENDRE = 0b00000010,
    ALLUMER_LED = 0b01000100,
    ETEINDRE_LED = 0b01000101,
    JOUER_SON = 0b01001000,
    ARRETER_SON = 0b00001001,
    ARRETER_MOTEURS_1 = 0b01100000 ,
    ARRETER_MOTEURS_2 = 0b01100001,
    AVANCER = 0b01100010, 
    RECULER = 0b01100011, 
    TOURNER_DROITE = 0b01100100,
    TOURNER_GAUCHE = 0b01100101, 
    DEBUT_BOUCLE = 0b11000000, 
    FIN_BOUCLE = 0b11000001, 
    FIN = 0b11111111
};

class Lecture
{
public:
    Lecture();    
    void initialiserLecture();
    void lireMemoire();
    void faireInstruction(uint8_t instruction, uint8_t operande);

private:
    uint16_t adresse_;
    uint8_t donnee_;
    uint8_t instruction_;
    uint8_t operande_;

    uint16_t adresseBoucle_;
    uint8_t compteurBoucle_;

    Del del_;
    //PontH moteur_;
    Memoire24CXXX mem_;
    Communication com_;

    bool programmeFini_;
};