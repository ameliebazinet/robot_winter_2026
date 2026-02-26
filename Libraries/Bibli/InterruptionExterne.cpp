#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Headers/InterruptionExterne.hpp"


void initialisation(int indiceInt)
{
	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'être interrompu alors que
	// le microcontrôleur n'est pas prêt...

	cli();

	// configurer et choisir les ports pour les entrées
	// et les sorties. DDRx... Initialisez bien vos variables

	DDRA |= (1 << PA0) | (1 << PA1);
	DDRD &= ~(1 << PD2);

	// cette procédure ajuste le registre EIMSK
	// de l’ATmega324PA pour permettre les interruptions externes

	EIMSK |= (1 << INT0);

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA

	EICRA |= (1 << ISC00);

	// sei permet de recevoir à nouveau des interruptions.

	sei();
}