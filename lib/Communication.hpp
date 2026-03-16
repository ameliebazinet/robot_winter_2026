// Fichier : Communication.hpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (...), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Cette classe implémente les méthodes pour la communication série via UART. 
// Elle permet d'initialiser la communication, de transmettre des données, des chaînes de caractères et des messages formatés.

#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <stdarg.h>

class Communication 
{
public:
    // Initialise la communication UART avec les paramètres requis
    void initialisationUART(void);

    // Transmet une donnée de type uint8_t via UART
    void transmissionUART(uint8_t donnee);

    // Transmet une chaîne de caractères via UART
    void transmissionChaine(const char* message);

    // Transmet une chaîne de caractères formatée via UART (similaire à printf)
    void transmissionFormatee(const char* format, ...);
};