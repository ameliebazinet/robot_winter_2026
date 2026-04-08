// Fichier : PontH.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Implémentation des méthodes pour la génération de signal PWM à l'aide de la minuterie 0.
// Envoi du signal PWM sur le pont en H pour le controle des roues.

#include "PontH.hpp"
const uint8_t VITESSE_TOURNER = 120;

void PontH::initialiserRegistre()
{
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
}

void PontH::configurer(bool directionGauche, uint8_t ratioGauche, bool directionDroite, uint8_t ratioDroite)
{
    Minuterie::Minuterie0::partirPWM(ratioGauche, ratioDroite);

    if (directionGauche == 0) {
        // Avance
        PORTB &= ~(1 << PB2);
    }
    else {
        // Recule
        PORTB |= (1 << PB2);
    }

    if (directionDroite == 0) {
        // Avance
        PORTB &= ~(1 << PB5);
    }
    else {
        // Recule
        PORTB |= (1 << PB5);
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

void PontH::tourner90DegresDroite()
{
    uint16_t delaiTournerDroite = 1050;
    initialiserRegistre();
    tournerDroite(VITESSE_TOURNER); 
    _delay_ms(delaiTournerDroite); 
    arreter();
}

void PontH::tourner90DegresGauche()
{
    uint16_t delaiTournerGauche = 1050;
    initialiserRegistre();
    tournerGauche(VITESSE_TOURNER); 
    _delay_ms(delaiTournerGauche); 
    arreter();

}

void PontH::tourner180()
{
    initialiserRegistre();
    tournerGauche(140); 
    _delay_ms(1400); 
    arreter();
}

void PontH::arreter()
{
    configurer(0, 0, 0, 0);
}
