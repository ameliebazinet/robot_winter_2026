// Fichier : debug.h
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (...), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Cette classe implémente les méthodes pour la manipulation d'une DEL à deux broches.

#define F_CPU 8000000UL
#include "Del.hpp"
#include <util/delay.h>

Del::Del(volatile uint8_t &port, uint8_t pin1, uint8_t pin2)
:   port_(port), 
    pin1_(pin1 & 0b111), 
    pin2_(pin2 & 0b111)
{
    
    // permet d'accéder au registre de direction (DDRx), dans la documentation
    // les registres associés à un port sont placés à des addresses 
    // concécutive en mémoire. En effectuant &port - 1, on accède à DDRx. 
    volatile uint8_t* ddr = &port-1;
    *ddr |= ((1 << pin1) | (1 << pin2));
}

void Del::allumerCouleur(Couleur couleur)
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

void Del::allumerCouleurAmbre()
{
    const uint8_t DELAI_AMBRE = 5;
    allumerCouleur(Couleur::ROUGE);
    _delay_ms(DELAI_AMBRE);
    allumerCouleur(Couleur::VERT);
    _delay_ms(DELAI_AMBRE);
}
