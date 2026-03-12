#include "InterruptionExterne.hpp"

void InterruptionExterne::activerInterruptionsGlobales()
{
    sei();
}

void InterruptionExterne::desactiverInterruptionsGlobales()
{
	cli();
}

void InterruptionExterne::activerInterruption(uint8_t indiceInt)
{
    EIMSK |= (1 << indiceInt);
}

void InterruptionExterne::desactiverInterruption(uint8_t indiceInt)
{
    EIMSK &= ~(1 << indiceInt);
}

// Lit le flag d'interruption (EIFR) pour savoir si une INT est en attente
bool InterruptionExterne::estEnAttente(uint8_t indiceInt)
{
    return (EIFR & (1 << indiceInt)) != 0;
}

void InterruptionExterne::changerDetectionInterruption(uint8_t indiceInt, uint8_t detectionInterruption)
{
    desactiverInterruptionsGlobales();
    desactiverInterruption(indiceInt);
    initialisation(indiceInt, detectionInterruption);
    activerInterruption(indiceInt);
}

bool InterruptionExterne::estActiveeBroche(uint8_t indiceInt)
{
    switch (indiceInt) {
        case 0: return (PIND & (1 << PD2)) != 0;
        case 1: return (PIND & (1 << PD3)) != 0;
        case 2: return (PINB & (1 << PB2)) != 0;
        default: return false;
    }
}

void InterruptionExterne::effacerFlag(uint8_t indiceInt)
{
    EIFR |= (1 << indiceInt); 
}

void InterruptionExterne::initialisation(uint8_t indiceInt, uint8_t detectionInterruption)
{
	desactiverInterruptionsGlobales();
    desactiverInterruption(indiceInt);
    effacerFlag(indiceInt);
	
	
    switch(indiceInt) {
        case 0: // INT0
            DDRD &= ~(1 << PD2);
            EICRA &= ~((1 << ISC00) | (1 << ISC01));
            switch(detectionInterruption) {
                case 0: 
					break;
                case 1: 
					EICRA |= (1 << ISC00); 
					break;
                case 2: 
					EICRA |= (1 << ISC01); 
					break;
                case 3: 
					EICRA |= (1 << ISC00) | (1 << ISC01); 
					break;
            }
            break;

        case 1: // INT1
            DDRD &= ~(1 << PD3);
            EICRA &= ~((1 << ISC10) | (1 << ISC11));
            switch(detectionInterruption) {
                case 0: 
					break;
                case 1: 
					EICRA |= (1 << ISC10); 
					break;
                case 2: 
					EICRA |= (1 << ISC11); 
					break;
                case 3: 
					EICRA |= (1 << ISC10) | (1 << ISC11); 
					break;
            }
            break;

        case 2: // INT2
            DDRB &= ~(1 << PB2);
            EICRA &= ~((1 << ISC20) | (1 << ISC21));
            switch(detectionInterruption) {
                case 0: 
					break;
                case 1: 
					EICRA |= (1 << ISC20); 
					break;
                case 2: 
					EICRA |= (1 << ISC21); 
					break;
                case 3: 
					EICRA |= (1 << ISC20) | (1 << ISC21); 
					break;
            }
            break;

        default: 
			break; 
    }

    activerInterruption(indiceInt);
    activerInterruptionsGlobales();
}
