#include "lecture/lecture.hpp"
#include "ecriture/ecriture.hpp"
#include "modes/execution.hpp"
#include "modes/instruction.hpp"
#include "modes/rapport.hpp"

volatile bool boutonClique;
volatile bool tempsEcoule;

int main()
{
    Lecture l;

    uint8_t nPersonnesLocalA, 
            nObjetsLocalB, 
            nObjetsLocalC, 
            nPersonnesLocalD, 
            nZonesEndommageesCouloirEst,
            nZonesEndommageesCouloirOuest;

    while (true)
    {
    // Trouve le mode (fait dans lecture)
    Mode mode = l.selectionnerMode(boutonClique, tempsEcoule);

    // EXECUTER instruction, rapport ou "execution" (modes/whatever)
    switch (mode)
    {
        case INSTRUCTION:
            faireInstruction();
            break;
    
        case EXECUTION:
            faireExecution(nPersonnesLocalA, 
                           nObjetsLocalB, 
                           nObjetsLocalC, 
                           nPersonnesLocalD, 
                           nZonesEndommageesCouloirEst,
                           nZonesEndommageesCouloirOuest);
            break;

        case RAPPORT:
            genererRapport(nPersonnesLocalA, 
                           nObjetsLocalB, 
                           nObjetsLocalC, 
                           nPersonnesLocalD, 
                           nZonesEndommageesCouloirEst,
                           nZonesEndommageesCouloirOuest);
            break;
        }
    }
}