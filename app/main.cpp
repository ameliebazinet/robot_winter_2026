#include "lecture/lecture.hpp"
#include "ecriture/ecriture.hpp"
#include "modes/execution.hpp"
#include "modes/instruction.hpp"
#include "modes/rapport.hpp"
#include "../lib/Son.hpp"

volatile bool boutonClique = false;
volatile bool tempsEcoule = false;

ISR(INT0_vect) 
{
    boutonClique = true;
}

ISR(TIMER1_COMPA_vect) {
    Minuterie::Minuterie1::miseAJourCompteur(tempsEcoule);
}



int main()
{ 
    Communication c;
    c.initialisationUART();
    _delay_ms(1000);

    Lecture l;
    l.initialiserLecture();
    
    uint8_t nPersonnesLocalA = 0;
    uint8_t nObjetsLocalB = 0;
    uint8_t nObjetsLocalC = 0;
    uint8_t nPersonnesLocalD = 0;
    uint8_t nZonesEndommageesCouloirEst = 0;
    uint8_t nZonesEndommageesCouloirOuest = 0;

    sei(); 
    Mode mode = l.selectionnerMode(boutonClique, tempsEcoule);

    switch (mode)
    {
        case INSTRUCTION:
            faireInstruction(l);
            break;
    
        case EXECUTION:
            l.lireMemoire();  
            faireExecution(nPersonnesLocalA, 
                           nObjetsLocalB, 
                           nObjetsLocalC, 
                           nPersonnesLocalD, 
                           nZonesEndommageesCouloirEst,
                           nZonesEndommageesCouloirOuest,
                           tempsEcoule);
            break;

        case RAPPORT:
            genererRapportDepuisMemoire();
            break;
    }

    while(true) {}
}