#include <avr/io.h>
#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>

enum Etat 
{
    SORTIR_STATIONNEMENT,
    PREMIER_COULOIR_SUD,
    COULOIR_COTE,

    COULOIR_NORD,
    PIECE_A_D,
    PIECE_B_C,

    DERNIER_COULOIR_SUD,

    ENTRER_STATIONNEMENT
};

void suivreCouloir();
void tournerCouloirGauche();
void tournerCouloirDroite();
void tournerBoutCouloir();
void sortirStationnementHoraire();
void sortirStationnementAntihoraire();
void parcourirCouloir();
void executerSallesAD();
void executerSallesBC();
void entrerStationnementHoraire(Lecture& l);
void entrerStationnementAntihoraire(Lecture& l);
void tournerDroite();
void faireExecution(uint8_t& nPersonnesLocalA,
                    uint8_t& nObjetsLocalB,
                    uint8_t& nObjetsLocalC,
                    uint8_t& nPersonnesLocalD,
                    uint8_t& nZonesEndommageesCouloirEst, 
                    uint8_t& nZonesEndommageesCouloirOuest,
                    volatile bool& tempsEcoule);