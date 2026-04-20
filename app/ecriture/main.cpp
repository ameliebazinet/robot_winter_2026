// Fichier : main.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Programme principal du mode écriture.
// Reçoit les paramètres de configuration via UART et les écrit en EEPROM.
// Ce main et ce Makefile ne sont pas utilisés durant l'execution du programme final
// et servent à tester l'ecriture UART.

#include "ecriture.hpp"

// Commandes à entrer dans le terminal pour écriture sur EEPROM.
// % progmem -o programme.bin programme.txt
// % serieViaUSB -e -f programme.bin

int main() 
{
    ecrireDepuisUART();
}