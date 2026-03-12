#include <avr/io.h>

// Cette class prend en consideration que les 2 pairs de pins du pont H
// sont connecté par un signal pwm pour le on/off et une autre pin pour la direction chaque.
// Doit etre connecté au port de sortie de la minuterie 0
class PontH
{
public:
    PontH(volatile uint8_t &port, uint8_t pin1, uint8_t pin2, uint8_t pwm1, uint8_t pwm2);

    void avancer(uint8_t ratio, int tempsMs);
    void reculer(uint8_t ratio, int tempsMs);
    void tournerDroite(uint8_t ratio, int tempsMs);
    void tournerGauche(uint8_t ratio, int tempsMs);
    void arreter();

private:
    volatile uint8_t &port_;
    uint8_t pinDirectionDroite_;
    uint8_t pinDirectionGauche_;
    uint8_t pinPwmDroite_;
    uint8_t pinPwmGauche_;
};