#include <avr/io.h>
#include "memoire_24.h"
#include "Communication.hpp"


void genererRapport(uint8_t nPersonnesLocalA,uint8_t nObjetsLocalB,uint8_t nObjetsLocalC,uint8_t nPersonnesLocalD,
uint8_t nZonesEndommageesCouloirEst, uint8_t nZonesEndommageesCouloirOuest);
void ecrireLigne(Communication com, bool conformite,const char* nom, uint8_t nombre, const char* detail);