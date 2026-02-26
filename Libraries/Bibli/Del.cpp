# include "Del.hpp"

Del::Del(volatile uint8_t &port, uint8_t pin1, uint8_t pin2)
: pin1_(pin1 & 0b111)
{

    *(&port-1) |= ((1 << pin1) | (1 << pin2));
}

Del::~Del()
{

}



void ajusterCouleur(Couleur couleur)
{
    if (couleur == Couleur::VERT) {
        port |= (1 << pin1);
        port &= ~(1 << pin2);
    
        else if (couleur == Couleur::ETEINT) {
        port &= ~(1 << pin1);
        port &= ~(1 << pin2);
        }
    else if (couleur == Couleur::ROUGE) {
        port &= ~(1 << pin1);
        port |= (1 << pin2);
        }
};
