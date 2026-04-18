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
            c.transmissionChaine("mode instruction entre\r\n");
            faireInstruction(l);
            c.transmissionChaine("fin");
            break;
    
        case EXECUTION:
            c.transmissionChaine("mode execution entre\r\n");

            l.lireMemoire();  
            faireExecution(nPersonnesLocalA, 
                           nObjetsLocalB, 
                           nObjetsLocalC, 
                           nPersonnesLocalD, 
                           nZonesEndommageesCouloirEst,
                           nZonesEndommageesCouloirOuest,
                           tempsEcoule);
            c.transmissionChaine("fin");

            break;

        case RAPPORT:
            c.transmissionChaine("mode rapport entre\r\n");
            genererRapportDepuisMemoire();
            c.transmissionChaine("fin");

            break;
    }


    while(true) {}
}





// #include "lecture/lecture.hpp"
// #include "ecriture/ecriture.hpp"
// #include "modes/execution.hpp"
// #include "modes/instruction.hpp"
// #include "modes/rapport.hpp"
// #include "../lib/Son.hpp"

// volatile bool boutonClique = false;
// volatile bool tempsEcoule = false;

// ISR(INT0_vect) {
//     boutonClique = true;
// }

// ISR(TIMER1_COMPA_vect) {
//     Minuterie::Minuterie1::miseAJourCompteur(tempsEcoule);
// }

// int main()
// { 
//     CapteurInfra ci;
//     Communication c;
//     c.initialisationUART();
//     //while(1){
//     //    ci.lireVoltage();
//     //    c.transmissionFormatee(" v = %d \r\n", ci.getVoltage());
//     //}

//     // Lecture l;
//     // l.initialiserLecture();
//     // l.lireMemoire();
//     sei();
//     Son::initialiserPiezo();
//     uint8_t nPersonnesLocalA = 0, 
//             nObjetsLocalB = 0, 
//             nObjetsLocalC = 0, 
//             nPersonnesLocalD = 0, 
//             nZonesEndommageesCouloirEst = 0,
//             nZonesEndommageesCouloirOuest = 0;

//     faireExecution(nPersonnesLocalA, nObjetsLocalB, nObjetsLocalC, nPersonnesLocalD,
//                 nZonesEndommageesCouloirEst, nZonesEndommageesCouloirOuest, tempsEcoule);
        
//     // while (true)
//     // {
//     // // Trouve le mode (fait dans lecture)
//     // Mode mode = l.selectionnerMode(boutonClique, tempsEcoule);
    
//     // // EXECUTER instruction, rapport ou "execution" (modes/whatever)
//     //     switch (mode)
//     //     {
//     //         case INSTRUCTION:
//     //             Son::jouer(46);
//     //             _delay_ms(1000);
//     //             Son::arreter();
//     //             faireInstruction(l);
//     //             break;
        
//     //         case EXECUTION:
//     //             // Son::jouer(69);
//     //             // _delay_ms(1000);
//     //             // Son::arreter();

//     //             faireExecution(nPersonnesLocalA, 
//     //                            nObjetsLocalB, 
//     //                            nObjetsLocalC, 
//     //                            nPersonnesLocalD, 
//     //                            nZonesEndommageesCouloirEst,
//     //                            nZonesEndommageesCouloirOuest,
//     //                            tempsEcoule);
//     //             break;

//     //         case RAPPORT:
//     //             Son::jouer(80);
//     //             _delay_ms(1000);
//     //             Son::arreter();
//     //             // genererRapport(nPersonnesLocalA, 
//     //             //                nObjetsLocalB, 
//     //             //                nObjetsLocalC, 
//     //             //                nPersonnesLocalD, 
//     //             //                nZonesEndommageesCouloirEst,
//     //             //                nZonesEndommageesCouloirOuest);
//     //             break;
//     //     }
//     // }
// }