#include <avr/io.h>
#include "PontH.hpp"
#include "Minuterie.hpp"

using namespace Minuterie;

PontH::PontH(volatile uint8_t &port, 
             uint8_t pinDirectionDroite, 
             uint8_t pinDirectionGauche, 
             uint8_t pinPwmDroite, 
             uint8_t pinPwmGauche)
:   port_(port), 
    pinDirectionDroite_(pinDirectionDroite & 0b111), 
    pinDirectionGauche_(pinDirectionGauche & 0b111),
    pinPwmDroite_(pinPwmDroite & 0b111),
    pinPwmGauche_(pinPwmGauche & 0b111)
{
    *(&port-1) |= (1 << pinDirectionDroite) | 
                  (1 << pinDirectionGauche) | 
                  (1 << pinPwmDroite) | 
                  (1 << pinPwmGauche);
}

void PontH::avancer(uint8_t ratio, int tempsMs)
{
    // pinDirectionDroite_ <= 0
    // pinDirectionGauche_ <= 0
    Minuterie0::PartirPWM(ratio);
    Minuterie1::partirMinuterie(tempsMs, A);
}
void PontH::reculer(uint8_t ratio, int tempsMs)
{
    // pinDirectionDroite_ <= 1
    // pinDirectionGauche_ <= 1

}
void PontH::tournerDroite(uint8_t ratio, int tempsMs)
{
    // droite desactivé
    // pinDirectionGauche_ <= 0

}
void PontH::tournerGauche(uint8_t ratio, int tempsMs)
{
    // pinDirectionDroite_ <= 0
    // gauche desactivé
}
void PontH::arreter()
{
}