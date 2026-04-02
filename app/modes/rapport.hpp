#include <avr/io.h>
#include "memoire_24.h"
#include "Communication.hpp"


void genererRapport(uint8_t nPersonnesLocalA,uint8_t nObjetsLocalB,uint8_t nObjetsLocalC,uint8_t nPersonnesLocalD,
uint8_t nZonesEndommageesCouloirEst, uint8_t nZonesEndommageesCouloirOuest)
{
    Communication com;
    bool conformiteA = (nPersonnesLocalA==0)? true:false;
    bool conformiteB = (nObjetsLocalB==0)? true:false;
    bool conformiteC = (nObjetsLocalC==0)? true:false;
    bool conformiteD = (nPersonnesLocalD==0)? true:false;
    bool conformiteEst = (nZonesEndommageesCouloirEst==0)? true:false;
    bool conformiteOuest = (nZonesEndommageesCouloirOuest==0)? true:false;
    com.transmissionFormatee("Emplacement \t\t Conformite \t\t detail \r\n");
    com.transmissionFormatee("Emplacement \\t Conformite \\t detail \r\n");
    



}