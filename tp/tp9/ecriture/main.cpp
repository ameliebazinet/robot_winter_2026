#include "ecriture.hpp"

// Commandes à entrer dans le terminal pour écriture sur EEPROM.
// % progmem -o programme.bin programme.txt
// % serieViaUSB -e -f programme.bin

int main() {
    ecrireDepuisUART();
}