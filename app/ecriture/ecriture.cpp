// Fichier : ecriture.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation des méthodes pour l'écriture de données en EEPROM.
// Permet de stocker les paramètres de configuration du robot reçus via UART.

#include "ecriture.hpp"
#include <util/delay.h>

const uint8_t DELAI_ECRITURE = 5;

void ecrireDepuisUART()
{
    Communication com;
    Memoire24CXXX memoire;

    com.initialisationUART();

    // Lire les deux octets de taille
    uint8_t octetHaut = com.receptionUART();
    uint8_t octetBas  = com.receptionUART();
    uint16_t tailleTotale = (octetHaut << 8) | octetBas;

    // Écrire les deux octets de taille dans EEPROM
    memoire.ecriture(0, octetHaut);
    _delay_ms(DELAI_ECRITURE);
    memoire.ecriture(1, octetBas);
    _delay_ms(DELAI_ECRITURE);

    // Recevoir et écrire le reste
    for (uint16_t i = 0; i < tailleTotale - 2; i++) {
        memoire.ecriture(i + 2, com.receptionUART());
        _delay_ms(DELAI_ECRITURE);
    }
}