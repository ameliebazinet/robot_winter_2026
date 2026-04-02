#include <avr/io.h>
#include "memoire_24.h"
#include "Communication.hpp"


// void genererRapport(uint8_t nPersonnesLocalA,uint8_t nObjetsLocalB,uint8_t nObjetsLocalC,uint8_t nPersonnesLocalD,
// uint8_t nZonesEndommageesCouloirEst, uint8_t nZonesEndommageesCouloirOuest)
// {
//     Communication com;
//     bool conformiteA = (nPersonnesLocalA==0)? true:false;
//     bool conformiteB = (nObjetsLocalB==0)? true:false;
//     bool conformiteC = (nObjetsLocalC==0)? true:false;
//     bool conformiteD = (nPersonnesLocalD==0)? true:false;
//     bool conformiteEst = (nZonesEndommageesCouloirEst==0)? true:false;
//     bool conformiteOuest = (nZonesEndommageesCouloirOuest==0)? true:false;
//     com.transmissionFormatee("Emplacement \t\t Conformite \t\t detail \r\n");
//     com.transmissionOccurence('-',15);

//     ecrireLigne(com, conformiteA, "Local A", nPersonnesLocalA);
//     ecrireLigne(com, conformiteB, "Local B", nObjetsLocalB);
//     ecrireLigne(com, conformiteC, "Local C", nObjetsLocalC);
//     ecrireLigne(com, conformiteD, "Local D", nPersonnesLocalD);
//     ecrireLigne(com, conformiteOuest, "Couloir OUEST", nZonesEndommageesCouloirOuest);
//     ecrireLigne(com, conformiteEst, "Couloir EST", nZonesEndommageesCouloirEst);

// }
// void ecrireLigne(Communication com, bool conformite,const char* nom, uint8_t nombre)
// {
//     if(conformite) com.transmissionFormatee("%s :\t oui \r\n",nom);
//     else com.transmissionFormatee("%s :\t\t non\t\t %d zones endommagees \r\n",nom,nombre);
// }