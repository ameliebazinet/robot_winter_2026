#include "execution.hpp"
#include <avr/io.h>

enum class Etat 
{
    SORTIR_STATIONNEMENT,

    PREMIER_COULOIR_SUD,
    PREMIER_COULOIR_LONG,

    COULOIR_NORD,
    PIECE_A_D,
    PIECE_B_C,

    DERNIER_COULOIR_LONG,
    DERNIER_COULOIR_SUD,

    ENTRER_STATIONNEMENT
};

void sortirStationnement() {}

void parcourirCouloir() {}

void scanPoteaux() {} // bip quand poteaux A D

void compterPersonnes() {} // B C compter tape

void entrerStationnement() {}

void faireExecution() 
{
    uint8_t compteurPiecesNord = 0;
    Etat etat = SORTIR_STATIONNEMENT;
    
    switch (etat)
    {
        case SORTIR_STATIONNEMENT:
            // quand tu sens la derniere ptite coche selon place parking 
            // next state : premier_couloir_sud QUAND arrivé devant
            break;
        case PREMIER_COULOIR_SUD:
            // rouler jusqu'au bout
            // tourne 90
            // next state : PREMIER_COULOIR_LONG quand fini de tourner
            break;
        case PREMIER_COULOIR_LONG:
            // compter obstacles en se bornant aux murs
            // tourner 90
            // next state : COULOIR_NORD quand fini tourner
            break;
        case COULOIR_NORD:
            // roule jusqu'a porte de A,B,C,D
            // compteur part a 0
            // si compteur a 0 ou 3 on passe a PIECE_A_D
            // sinon compteur 1 ou 2 : PIECE_B_C
            // compteur++

            // quand compteur = 4 : rouler jusqua ligne pleine
            // virage 90
            // next State DERNIER_COULOIR_LONG
            break;
        case PIECE_A_D:
            // y scan calisse
            // pis y retourne
            // next state : COULOIR_NORD
            break;
        case PIECE_B_C:
            // voir plus haut (mais tapes au lieu de poteaux)
            break;
        case DERNIER_COULOIR_LONG:
            // compter obstacles en se bornant aux murs
            // tourner 90
            // next state : DERNIER_COULOIR_SUD quand fini tourner
            break;
        case DERNIER_COULOIR_SUD:
            // rouler borné jusqu'a la fin
            // quand tu sens la ptite coche mais rien d'autre next state ENTRER_STATIONNEMENT
            break;
        case ENTRER_STATIONNEMENT:
            // SI sens horaire : nb coches avant park = 5 - valeurPlaceParking
            // SI sens antihoraire : nb coches avant park = valeurPlaceParking
            break;
    }
}
