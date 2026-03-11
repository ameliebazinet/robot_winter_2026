#include <avr/io.h>
#include "Communication.hpp"


void Communication::initialisationUART(void) 
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    UCSR0C &= ~(1 << UPM01);
    UCSR0C &= ~(1 << UPM00);
    UCSR0C &= ~(1 << USBS0);
    UCSR0C &= ~(1 << UCSZ02);
    UCSR0C |= (1 << UCSZ01);
    UCSR0C |= (1 << UCSZ00);

}

void Communication::transmissionUART(uint8_t donnee) 
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = donnee;
}

void Communication::transmissionChaine(const char* message) 
{
    while (*message) {
        Communication::transmissionUART((uint8_t)*message);
        message++;
    }
}