#include "execution.hpp"

void suivreCouloir()
{
    CapteurLigne capteur;
    PontH::initialiserRegistre();

    PontH::avancer(255);
    _delay_ms(250);

    while (!capteur.estSurLignePleine()) {

        if (capteur.estTropADroite()) {
            PontH::configurer(1, 185, 0, 185);
        }

        else if (capteur.estTropAGauche()) {
            PontH::configurer(0, 185, 1, 185);
        }

        else {
            PontH::avancer(100);
        }
    }
    PontH::arreter();
}

void sortirStationnement() 
{
    CapteurLigne capteur; 
    PontH::tourner180(); 
    PontH::arreter();


    while (!(capteur.estSurLignePleine()))
    {
        PontH::avancer(128);
    }
    PontH::arreter(); 
}

void parcourirCouloir() {}

void scanPoteaux() {} // bip quand poteaux A D

void compterPersonnes() {} // B C compter tape

void entrerStationnement() {}

void tournerDroite()
{
   CapteurLigne capteur;
   PontH::arreter();
   _delay_ms(1000);
    PontH::avancer(255);
    _delay_ms(100);
   PontH::tourner90DegresDroite();
   suivreCouloir();
    
}

void faireExecution(uint8_t& nPersonnesLocalA,
                    uint8_t& nObjetsLocalB,
                    uint8_t& nObjetsLocalC,
                    uint8_t& nPersonnesLocalD,
                    uint8_t& nZonesEndommageesCouloirEst, 
                    uint8_t& nZonesEndommageesCouloirOuest) 
{
    uint8_t compteurPiecesNord = 0;
    Etat etat = SORTIR_STATIONNEMENT;
    
    while (true) {
        switch (etat)
        {
            case SORTIR_STATIONNEMENT:
                parcourirCouloir();
                // quand tu sens la derniere ptite coche selon place parking 
                etat = PREMIER_COULOIR_SUD;
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
}
