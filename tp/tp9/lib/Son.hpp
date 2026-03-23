// Fichier : Son.hpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Classe pour jouer des notes MIDI via le mode CTC de la minuterie 1 connectée à une cellule piézoélectrique sur OC1A (PD5).

#pragma once
#include <stdint.h>

class Son
{
public:
    // Initialise PD5 en sortie (fréquence à laquelle est connectée la cellule piézoélectrique) et PD4 en sortie à 0 (ground).
    static void initialiserPiezo();

    // Joue la note MIDI donnée (45 à 81). Retourne false si la note est hors plage (la commande est ignorée).
    static bool jouer(uint8_t noteMidi);

    // Arrête le son en cours.
    static void arreter();
};