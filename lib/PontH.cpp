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
