#include "Del.hpp"
#include <avr/delay.h>

Del::Del(volatile uint8_t &port, uint8_t pin1, uint8_t pin2)
:   port_(port), 
    pin1_(pin1 & 0b111), 
    pin2_(pin2 & 0b111)
{
    *(&port-1) |= ((1 << pin1) | (1 << pin2));
    // Dans la documentation une adresse de différence entre port et pin. 
}

void Del::ajusterCouleur(Couleur couleur)
{
    if (couleur == Couleur::ETEINT) 
    {   
        port_ &= ~(1 << pin1_);
        port_ &= ~(1 << pin2_);
    }

    else if (couleur == Couleur::VERT) 
    {
        port_ |= (1 << pin1_);
        port_ &= ~(1 << pin2_);
    }

    else if (couleur == Couleur::ROUGE) 
    {
        port_ &= ~(1 << pin1_);
        port_ |= (1 << pin2_);
    }
};

void Del::ajusterAmbre()
{
    const uint8_t DELAI_AMBRE = 5;
    ajusterCouleur(Couleur::ROUGE);
    _delay_ms(DELAI_AMBRE);
    ajusterCouleur(Couleur::VERT);
    _delay_ms(DELAI_AMBRE);
}
