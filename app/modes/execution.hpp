#include <avr/io.h>
#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>

enum Etat 
{
    SORTIR_STATIONNEMENT,

    COULOIRS_COTES,

    COULOIR_NORD,
    PIECE_A_D,
    PIECE_B_C,

    ENTRER_STATIONNEMENT
};

void suivreCouloir();
void longerLigneGauche(); 
void longerLigneDroite();
void sortirStationnementHoraire();
void sortirStationnementAntiHoraire();
void parcourirCouloir();
void executerSallesAD();
void executerSallesBC();
void entrerStationnementHoraire();
void tournerDroite();
void faireExecution(uint8_t& nPersonnesLocalA,
                    uint8_t& nObjetsLocalB,
                    uint8_t& nObjetsLocalC,
                    uint8_t& nPersonnesLocalD,
                    uint8_t& nZonesEndommageesCouloirEst, 
                    uint8_t& nZonesEndommageesCouloirOuest,
                    volatile bool& tempsEcoule);