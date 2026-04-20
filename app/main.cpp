// Fichier : main.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Programme principal du robot.
// Initialise les interruptions, sélectionne le mode d'opération et exécute le mode choisi.

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

// Table d'états de la sélection de mode (Mode) :
//
// +-------------+--------------------------------------------+------------------------------+
// | Mode        | Condition de sélection (bouton/minuterie)  | Action                       |
// +-------------+--------------------------------------------+------------------------------+
// | INSTRUCTION | bouton appuyé pendant phase verte (0-2s)   | faireInstruction()           |
// | RAPPORT     | bouton appuyé pendant phase rouge (3-5s)   | genererRapportDepuisMemoire()|
// | EXECUTION   | aucun bouton appuyé (délai écoulé)         | faireExecution()             |
// +-------------+--------------------------------------------+------------------------------+

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