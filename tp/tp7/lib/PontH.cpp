#include <avr/io.h>
#include "PontH.hpp"
#include "Minuterie.hpp"

using namespace Minuterie;

PontH::PontH(volatile uint8_t &port,
             uint8_t pinDirectionDroite,
             uint8_t pinDirectionGauche,
             uint8_t pinPwmDroite,
             uint8_t pinPwmGauche)
    : port_(port),
      pinDirectionDroite_(pinDirectionDroite & 0b111),
      pinDirectionGauche_(pinDirectionGauche & 0b111),
      pinPwmDroite_(pinPwmDroite & 0b111),
      pinPwmGauche_(pinPwmGauche & 0b111)
{
    volatile uint8_t *ddr = &port - 1;
    *ddr |= (1 << pinDirectionDroite) |
            (1 << pinDirectionGauche) |
            (1 << pinPwmDroite) |
            (1 << pinPwmGauche);
}

void PontH::avancer(uint8_t ratio)
{
    port_ &= ~(1 << pinDirectionDroite_);
    port_ &= ~(1 << pinDirectionGauche_);
    Minuterie0::PartirPWM(ratio, ratio);
}
void PontH::reculer(uint8_t ratio)
{
    // pinDirectionDroite_ <= 1
    // pinDirectionGauche_ <= 1
}
void PontH::tournerDroite(uint8_t ratio)
{
    // pinDirectionDroite_ <= 1
    // pinDirectionGauche_ <= 0
}
void PontH::tournerGauche(uint8_t ratio)
{
    // pinDirectionDroite_ <= 0
    // pinDirectionGauche_ <= 1
}
void PontH::arreter()
{
}

void PontH::configurer(uint8_t ratioDroite, uint8_t ratioGauche)
{
}