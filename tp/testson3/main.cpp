// Fichier : main.cpp
// Description : Test de la classe Son — joue chaque note MIDI du tableau (45 à 81)
//               avec une pause entre chaque, teste les cas limites, et vérifie
//               que le son continue pendant un "déplacement" simulé.

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Son.hpp"

// Durée d'écoute de chaque note (ms)
static const uint16_t DUREE_NOTE_MS  = 500;
// Silence entre les notes (ms)
static const uint16_t SILENCE_MS     = 150;

// Broche de la DEL pour feedback visuel (ex: PA0 rouge, PA1 vert)
static const uint8_t PIN_DEL_ROUGE = PA0;
static const uint8_t PIN_DEL_VERT  = PA1;

void initialiserDEL()
{
    DDRA |= (1 << PIN_DEL_ROUGE) | (1 << PIN_DEL_VERT);
    PORTA &= ~((1 << PIN_DEL_ROUGE) | (1 << PIN_DEL_VERT));
}

void allumerRouge() { PORTA |=  (1 << PIN_DEL_ROUGE); PORTA &= ~(1 << PIN_DEL_VERT); }
void allumerVert()  { PORTA |=  (1 << PIN_DEL_VERT);  PORTA &= ~(1 << PIN_DEL_ROUGE); }
void eteindreDEL()  { PORTA &= ~((1 << PIN_DEL_ROUGE) | (1 << PIN_DEL_VERT)); }

void initialiserPiezo()
{
    // OC1A (PD5) : sortie signal
    // PD4        : masse virtuelle
    DDRD |= (1 << PD5) | (1 << PD4);
    PORTD &= ~((1 << PD5) | (1 << PD4));
}

int main()
{
    initialiserDEL();
    initialiserPiezo();

    // -------------------------------------------------------
    // TEST 1 : séquence de démarrage visuelle (2x rouge, 2x vert)
    // -------------------------------------------------------
    for (uint8_t i = 0; i < 2; i++) {
        allumerRouge();
        _delay_ms(300);
        eteindreDEL();
        _delay_ms(150);
    }
    for (uint8_t i = 0; i < 2; i++) {
        allumerVert();
        _delay_ms(300);
        eteindreDEL();
        _delay_ms(150);
    }

    _delay_ms(500);

    // -------------------------------------------------------
    // TEST 2 : gamme ascendante — notes 45 à 81
    //          DEL verte pendant chaque note valide
    // -------------------------------------------------------
    for (uint8_t note = 45; note <= 81; note++) {
        bool ok = Son::jouer(note);

        if (ok)
            allumerVert();
        else
            allumerRouge(); // ne devrait jamais arriver dans cette plage

        _delay_ms(DUREE_NOTE_MS);

        Son::arreter();
        eteindreDEL();
        _delay_ms(SILENCE_MS);
    }

    _delay_ms(500);

    // -------------------------------------------------------
    // TEST 3 : gamme descendante — notes 81 à 45
    // -------------------------------------------------------
    for (uint8_t note = 81; note >= 45; note--) {
        Son::jouer(note);
        allumerVert();
        _delay_ms(DUREE_NOTE_MS);
        Son::arreter();
        eteindreDEL();
        _delay_ms(SILENCE_MS);
    }

    _delay_ms(500);

    // -------------------------------------------------------
    // TEST 4 : notes hors plage → DEL rouge, pas de son
    //          Note 44 (en dessous) et note 82 (au dessus)
    // -------------------------------------------------------
    bool horsPlage1 = Son::jouer(44); // doit retourner false
    if (!horsPlage1)
        allumerRouge();               // rouge = rejet correct
    _delay_ms(600);
    eteindreDEL();
    _delay_ms(200);

    bool horsPlage2 = Son::jouer(82); // doit retourner false
    if (!horsPlage2)
        allumerRouge();
    _delay_ms(600);
    eteindreDEL();
    _delay_ms(200);

    _delay_ms(500);

    // -------------------------------------------------------
    // TEST 5 : son joué en continu pendant un "déplacement"
    //          Simule sgo + mav : le son continue pendant 2 s
    //          (la minuterie tourne seule, pas besoin d'interruption)
    // -------------------------------------------------------
    Son::jouer(69); // La 440 Hz
    allumerVert();

    // Simule le temps que prendrait un déplacement du robot
    for (uint8_t i = 0; i < 8; i++) {
        _delay_ms(250); // 8 x 250 ms = 2 s de son continu
    }

    Son::arreter();
    eteindreDEL();
    _delay_ms(500);

    // -------------------------------------------------------
    // TEST 6 : enchaînement rapide de 3 notes (Do-Mi-Sol, notes 60-64-67)
    //          Pour vérifier que reconfigurer la minuterie fonctionne
    // -------------------------------------------------------
    uint8_t accord[] = {60, 64, 67};
    for (uint8_t i = 0; i < 3; i++) {
        Son::jouer(accord[i]);
        allumerVert();
        _delay_ms(400);
        Son::arreter();
        eteindreDEL();
        _delay_ms(100);
    }

    _delay_ms(500);

    // -------------------------------------------------------
    // FIN : clignotement vert rapide x5 = succès
    // -------------------------------------------------------
    for (uint8_t i = 0; i < 5; i++) {
        allumerVert();
        _delay_ms(100);
        eteindreDEL();
        _delay_ms(100);
    }

    while (true) {} // boucle infinie
    return 0;
}