// Fichier : Son.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation de la classe Son. Utilisation du mode CTC de la minuterie 1 sur OC1A (PD5).
// Le fil noir de la cellule piézoélectrique est branché sur PD4 (ground)

#define F_CPU 8000000UL
#include <avr/io.h>
#include <math.h>
#include "Son.hpp"
#include "Minuterie.hpp"

using namespace Minuterie;

static const uint8_t  NOTE_MIN   = 45;
static const uint8_t  NOTE_MAX   = 81;
static const uint16_t PRESCALER  = 8;

static uint32_t frequenceHz(uint8_t noteMidi)
{
    // f = 440 Hz * 2^((note - 69) / 12)
    double exposant = (double)(noteMidi - 69) / 12.0;
    double frequence = 440.0 * pow(2.0, exposant);

    // On arrondit à l'entier le plus proche
    return (uint32_t)(frequence + 0.5);
}

bool Son::jouer(uint8_t noteMidi)
{
    if (noteMidi < NOTE_MIN || noteMidi > NOTE_MAX)
        return false;

    uint32_t frequence = frequenceHz(noteMidi);
    if (frequence == 0)
        return false;

    // OCR1A = F_CPU / (2 * prescaler * frequence) - 1
    uint16_t ocr1a = (uint16_t)(F_CPU / (2UL * PRESCALER * frequence)) - 1;

    // CTC, prescaler 8, TOGGLE sur OC1A, signal sur PD5
    Minuterie1::configurer(CTC1A, CTC1B, PRESCALER8, TOGGLE_A, DECONNECTE_B);
    OCR1A = ocr1a;
    return true;
}

void Son::arreter()
{
    Minuterie1::configurer(CTC1A, CTC1B, OFF, DECONNECTE_A, DECONNECTE_B);
    OCR1A = 0;
}