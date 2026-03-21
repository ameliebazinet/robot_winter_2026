// Fichier : PontH.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation des méthodes pour la génération de signal PWM à l'aide de la minuterie 2.
// Envoi du signal PWM sur le pont en H pour le controle des roues.


#include "PontH.hpp"

void PontH::initialiserRegistre()
{
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
}

void PontH::configurer(bool directionGauche, uint8_t ratioGauche, bool directionDroite, uint8_t ratioDroite)
{
    //On envoie ratioDroite sur PD7 et ratioGauche sur PD6
    Minuterie::Minuterie2::partirPWM(ratioDroite, ratioGauche);

    if (directionGauche == 0) {
        // Avance
        PORTD &= ~(1 << PD4);
    }
    else {
        // Recule
        PORTD |= (1 << PD4);
    }

    if (directionDroite == 0) {
        // Avance
        PORTD &= ~(1 << PD5);
    }
    else {
        // Recule
        PORTD |= (1 << PD5);
    }
}

void PontH::avancer(uint8_t ratio)
{
    configurer(0, ratio, 0, ratio);
}
void PontH::reculer(uint8_t ratio)
{
    configurer(1, ratio, 1, ratio);
}

void PontH::tournerDroite(uint8_t ratio)
{
    configurer(0, ratio, 1, ratio);
}
void PontH::tournerGauche(uint8_t ratio)
{
    configurer(1, ratio, 0, ratio);
}

void PontH::arreter()
{
    configurer(0, 0, 0, 0);
}

void PontH::tournerDroite90(uint8_t ratio)
{
    // fait par delay pour le moment. 
    // il est possible qu'elle ait besoin d'etre fait par interupton dans le futur.

    const int tempsTournerDroiteMs = 0; // a mesurer avec les batteries
    PontH::tournerDroite(ratio);
    attendreDelayMs(tempsTournerDroiteMs);
}
void PontH::tournerGauche90(uint8_t ratio)
{
    tournerGauche(ratio);
    // completer lorsque tournerDroite90 fini.

}

void attendreDelayMs(int tempsMs) {
    for(int i = 0; i < tempsMs; i++) {
        _delay_ms(1);
    }
}
