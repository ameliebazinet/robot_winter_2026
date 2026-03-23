#include "ecriture.hpp"
#include <util/delay.h>

void ecrireDepuisUART() {
    Communication com;
    Memoire24CXXX memoire;

    com.initialisationUART();

    // read the 2 size bytes
    uint8_t highByte = com.receptionUART();
    uint8_t lowByte  = com.receptionUART();
    uint16_t totalSize = (highByte << 8) | lowByte;

    // write the 2 size bytes to EEPROM
    memoire.ecriture(0, highByte);
    _delay_ms(5);
    memoire.ecriture(1, lowByte);
    _delay_ms(5);
    // receive and write the rest
    for (uint16_t i = 0; i < totalSize-2; i++) {
        memoire.ecriture(i + 2, com.receptionUART());
        _delay_ms(5);
    }
}