#pragma once 
#include <avr/io.h>
#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include "../lib/CapteurInfra.hpp"
#include "Del.hpp"
#include "../lecture/lecture.hpp"
#include <util/delay.h>

enum Etat 
{
    SORTIR_STATIONNEMENT,
    PREMIER_COULOIR_SUD,
    COULOIR_COTE,

    COULOIR_NORD,
    SALLE_A_D,
    SALLE_B_C,

    DERNIER_COULOIR_COTE,
    DERNIER_COULOIR_SUD,

    ENTRER_STATIONNEMENT
};


enum EtatCouloir {
    COULOIR,
    VERIFICATION_ENTREE,
    ENTREE_TROUVEE
};

void recalibrer(); 
void recalibrerVirage(Lecture& l);
void suivreCouloir(Lecture& l);
void tournerCouloirGauche(Lecture& l);
void tournerCouloirDroite(Lecture& l);
void tournerBoutCouloir(Lecture& l);
void sortirStationnement(Lecture& l);
void parcourirCouloir();
void executerSallesAD(Lecture& l);
void executerSallesBC(uint8_t& nObjetsLocal, volatile bool & tempsEcoule, Lecture& l);
void couloirNord(Lecture& l);
//void entrerStationnementHoraire(Lecture& l);
//void entrerStationnementAntihoraire(Lecture& l);
void tournerDroite();
void faireExecution(uint8_t& nPersonnesLocalA,
                    uint8_t& nObjetsLocalB,
                    uint8_t& nObjetsLocalC,
                    uint8_t& nPersonnesLocalD,
                    uint8_t& nZonesEndommageesCouloirEst, 
                    uint8_t& nZonesEndommageesCouloirOuest,
                    volatile bool& tempsEcoule);