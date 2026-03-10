#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "InterruptionExterne.hpp"

void initialisation(uint8_t indiceInt, uint8_t interruptSenseControl)
{
	cli();
	EIMSK |= (1 << indiceInt);
	
	// initialisation de l'interruption de Int0
	if (indiceInt == 0)
	{
		EICRA &= ~((1 << ISC00) | (1 << ISC01)); 
		DDRD &= ~(1 << PD2);
		if (interruptSenseControl == 0)
		{
			EICRA &= ~(1 << ISC00) & ~(1 << ISC01);
		}
		else if (interruptSenseControl == 1)
		{
			EICRA &= ~(1 << ISC01);
			EICRA |= (1 << ISC00);
		}
		else if (interruptSenseControl == 2)
		{
			EICRA &= ~(1 << ISC00);
			EICRA |= (1 << ISC01);
		}
		else if (interruptSenseControl == 3)
		{
			EICRA |= (1 << ISC00) | (1 << ISC01);
		}
	}

	// initialisation de l'interruption de Int1
	if (indiceInt == 1)
	{
		DDRD &= ~(1 << PD3);
		EICRA &= ~((1 << ISC10) | (1 << ISC11)); 
		if (interruptSenseControl == 0)
		{
			EICRA &= ~(1 << ISC10) & ~(1 << ISC11);
		}
		else if (interruptSenseControl == 1)
		{
			EICRA &= ~(1 << ISC11);
			EICRA |= (1 << ISC10);
		}
		else if (interruptSenseControl == 2)
		{
			EICRA &= ~(1 << ISC10);
			EICRA |= (1 << ISC11);
		}
		else if (interruptSenseControl == 3)
		{
			EICRA |= (1 << ISC10) | (1 << ISC11);
		}
	}

	// initialisation de l'interruption de Int2
	if (indiceInt == 2)
	{
		DDRB &= ~(1 << PB2);
		EICRA &= ~((1 << ISC20) | (1 << ISC21)); 
		if (interruptSenseControl == 0)
		{
			EICRA &= ~(1 << ISC20) & ~(1 << ISC21);
		}
		else if (interruptSenseControl == 1)
		{
			EICRA &= ~(1 << ISC21);
			EICRA |= (1 << ISC20);
		}
		else if (interruptSenseControl == 2)
		{
			EICRA &= ~(1 << ISC20);
			EICRA |= (1 << ISC21);
		}
		else if (interruptSenseControl == 3)
		{
			EICRA |= (1 << ISC20) | (1 << ISC21);
		}

	}
}

void desactiverInterruptionsGlobales()
{
	cli();
}

void activerInterruptionsGlobales()
{
    sei();
}

void desactiverInterruption(uint8_t indiceInt)
{
    EIMSK &= ~(1 << indiceInt);
}

void activerInterruption(uint8_t indiceInt)
{
    EIMSK |= (1 << indiceInt);
}

// Lire le flag d'interruption (EIFR) pour savoir si une INT est en attente
bool interruptionEnAttente(uint8_t indiceInt)
{
    return (EIFR & (1 << indiceInt)) != 0;
}

void changerSenseControl(uint8_t indiceInt, uint8_t interruptSenseControl)
{
    desactiverInterruption(indiceInt);
    initialisation(indiceInt, interruptSenseControl);
    activerInterruption(indiceInt);
}

bool lireEtatBroche(uint8_t indiceInt)
{
    return (EIFR & (1 << indiceInt)) != 0;
}

void effacerFlag(uint8_t indiceInt)
{
    EIFR |= (1 << indiceInt); 
}