// % progmem -o programme.bin programme.txt

// % serieViaUSB -e -f programme.bin

#include "ecriture.hpp"

int main() {
    Communication com;
    Memoire24CXXX memoire;

    com.initialisationUART();

    // read the 2 size bytes
    uint8_t highByte = com.receptionUART();
    uint8_t lowByte  = com.receptionUART();
    uint16_t totalSize = (highByte << 8) | lowByte;

    // write the 2 size bytes to EEPROM
    memoire.ecriture(0, highByte);
    memoire.ecriture(1, lowByte);

    // receive and write the rest
    for (uint16_t i = 2; i < totalSize; i++) {
        memoire.ecriture(i, com.receptionUART());
    }

    return 0;
}