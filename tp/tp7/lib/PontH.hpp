// Fichier : PontH.hpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Cette classe déclare les méthodes pour la generation de signal PWM à l'aide de la minuterie 2.
// Branchements pour fontionner:
//
//   PD4 => Direction roue gauche
//   PD5 => Direction roue droite
//   PD6 => Enable roue gauche
//   PD7 => Enable roue droite


#include "Minuterie.hpp"
#include <util/delay.h>

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