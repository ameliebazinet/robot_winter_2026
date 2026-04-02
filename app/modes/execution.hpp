#include <avr/io.h>
#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>

enum Etat 
{
    SORTIR_STATIONNEMENT,

    PREMIER_COULOIR_SUD,
    PREMIER_COULOIR_LONG,

    COULOIR_NORD,
    PIECE_A_D,
    PIECE_B_C,

    DERNIER_COULOIR_LONG,
    DERNIER_COULOIR_SUD,

    ENTRER_STATIONNEMENT
};

void suivreCouloir();
void sortirStationnement();
void parcourirCouloir();
void scanPoteaux();
void compterPersonnes();
void entrerStationnement();
void tournerDroite();
void faireExecution();