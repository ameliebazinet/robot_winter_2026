// Fichier : Communication.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation des méthodes pour la communication série via UART. 
// Permet d'initialiser la communication, de transmettre des données, des chaînes de caractères et des messages formatés.



#include <avr/io.h>
#include <stdio.h>
#include <stdarg.h>
#include "Communication.hpp"

void Communication::initialisationUART(void) {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void Communication::transmissionUART(uint8_t donnee) 
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = donnee;
}

void Communication::transmissionChaine(const char* message) 
{
    if (!message) {
        return;
    }
    
    while (*message) {
        transmissionUART((uint8_t)*message);
        message++;
    }
}

void Communication::transmissionFormatee(const char* format, ...) 
{
    char buffer[64];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    transmissionChaine(buffer);
}

uint8_t Communication::receptionUART() 
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

