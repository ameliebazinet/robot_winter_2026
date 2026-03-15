#include <avr/io.h>
#include "Minuterie.hpp"

// Cette class utilise la minuterie 2 pour la generation de signal PWM.
// Envoie ce signal PWM sur le pont en H pour le controle des roue.
//
// Branchement pour fontionner:
//
//   PD4 => Direction roue gauche
//   PD5 => Direction roue droite
//   PD6 => Enable roue gauche
//   PD7 => Enable roue droite
//
class PontH
{
public:
    // Fixe DDR et PORT pour l'utilisation des pins.
    static void initialiserRegistre();

    // Cette fonction laisse plus de liberté de configurer pour le choix de mouvement.
    // Les valeurs pour mouvement(Droite/Gauche) sont 0 pour avancer et 1 pour reculer.
    // Les ratios doivent etre compris entre 0 et 100 inclusivement.
    static void configurer(bool directionGauche, uint8_t ratioGauche, bool directionDroite, uint8_t ratioDroite);

    // Le ratio doit etre compris entre 0 et 100 inclusivement.
    static void avancer(uint8_t ratio);
    static void reculer(uint8_t ratio);

    // Cette fonction a un pivot de rotation est le centre du robot (entre les 2 roues).
    // Le ratio doit etre compris entre 0 et 100 inclusivement.
    static void tournerDroite(uint8_t ratio);
    static void tournerGauche(uint8_t ratio);

    static void arreter();
};