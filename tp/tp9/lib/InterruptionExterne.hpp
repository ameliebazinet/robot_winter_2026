// Fichier : InterruptionExterne.hpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Cette classe déclare les méthodes pour la gestion des interruptions externes. 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

class InterruptionExterne
{
public:
    // Active les interruptions globales en utilisant sei() 
    void activerInterruptionsGlobales();

    // Désactive les interruptions globales en utilisant cli()
    void desactiverInterruptionsGlobales();

    // Active l'interruption externe spécifiée par indiceInt (0, 1 ou 2)
    void activerInterruption(uint8_t indiceInt);

    // Désactive l'interruption externe spécifiée par indiceInt (0, 1 ou 2)
    void desactiverInterruption(uint8_t indiceInt);

    // Vérifie si l'interruption externe spécifiée par indiceInt est en attente
    bool estEnAttente(uint8_t indiceInt);

    // Efface le flag d'interruption de l'interruption externe spécifiée par indiceInt
    void changerDetectionInterruption(uint8_t indiceInt, uint8_t detectionInterruption);

    // Vérifie si la broche associée à l'interruption externe spécifiée par indiceInt est active
    bool estActiveeBroche(uint8_t indiceInt);

    // Efface le flag d'interruption de l'interruption externe spécifiée par indiceInt
    void effacerFlag(uint8_t indiceInt);

    // Initialise l'interruption externe spécifiée par indiceInt avec le mode de détection spécifié par detectionInterruption
    void initialisation(uint8_t indiceInt, uint8_t detectionInterruption);
};
