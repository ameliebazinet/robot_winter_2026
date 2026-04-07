#include "execution.hpp"
#include "../lib/CapteurInfra.hpp"
#include "Del.hpp"
#include "../lecture/lecture.hpp"

void parcourirCouloir() {}

void suivreCouloir()
{
    CapteurLigne capteur;
    Del del(PORTA, PA2, PA3);
    PontH::initialiserRegistre();

    uint8_t nObstacles = 0;
    bool estSurObstacleAvant = false;    

    PontH::avancer(255);
    _delay_ms(100);

    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = capteur.estObstacleAuCentre();
        
        if (estSurObstacleMaintenant && !estSurObstacleAvant)
            nObstacles++;

        if (estSurObstacleMaintenant)
            del.allumerCouleur(Del::Couleur::ROUGE);
        else
            del.allumerCouleur(Del::Couleur::ETEINT);

        estSurObstacleAvant = estSurObstacleMaintenant;

        if (capteur.estTropADroitePrecis()) {
            PontH::configurer(0, 70, 0, 90);
        }

        else if (capteur.estTropAGauchePrecis()) {
            PontH::configurer(0, 90, 0, 70);
        }
        else {
            PontH::avancer(90);
        }

        _delay_ms(50);
    }
    PontH::arreter();
}

void sortirStationnementHoraire() 
{
    CapteurLigne capteur; 
    PontH::tourner180(); 
    PontH::arreter();
    _delay_ms(1000);


    while (!(capteur.estSurLignePleine())) {
        PontH::avancer(150);
        _delay_ms(10);
        PontH::avancer(100);
    }
    PontH::arreter();
    _delay_ms(1000); 

    PontH::tournerDroite(255);
    _delay_ms(20);
    PontH::tournerDroite(100);
    _delay_ms(1000);

    PontH::arreter();
    _delay_ms(1000);

    bool couloirTrouve = false;
    while (!couloirTrouve) {
        if (capteur.estTropADroite() || capteur.estTropADroitePrecis()) {
            couloirTrouve = true;
            break;
        }
        else if (capteur.estTropAGauchePrecis()) {
            PontH::tournerDroite(120);
            _delay_ms(100);
        }
        else
            PontH::configurer(0, 90, 0, 130);
    }

    PontH::arreter();
}

void sortirStationnementAntiHoraire() 
{
    CapteurLigne capteur; 
    PontH::tourner180(); 
    PontH::arreter();
    _delay_ms(1000);

    while (!(capteur.estSurLignePleine())) {
        PontH::avancer(130);
        _delay_ms(10);
        PontH::avancer(100);
    }
    PontH::arreter();
    _delay_ms(1000); 

    PontH::tournerGauche(255);
    _delay_ms(100);
    PontH::tournerGauche(100);
    _delay_ms(1000);

    PontH::arreter();
    _delay_ms(1000);

    bool couloirTrouve = false;
    while (!couloirTrouve) {
        if (capteur.estTropAGauche() || capteur.estTropAGauchePrecis()) {
            couloirTrouve = true;
            break;
        }
        else if (capteur.estTropADroitePrecis()) {
            PontH::tournerGauche(120);
            _delay_ms(100);
        }
        else
            PontH::configurer(0, 130, 0, 90);
    }

    PontH::arreter();
    // {

    //     if(capteur.estTropAGauchePrecis())
    //         PontH::avancer(100);
    //     else
    //         PontH::configurer(0, 80, 0, 150);
    // }

}


void parcourirCouloir() {}

void scanPoteaux() {
    CapteurInfra ci;
    PontH pontH;
    Del del(PORTA, PA0, PA1);
    pontH.initialiserRegistre();
    
    const uint16_t DUREE_TOTALE_MS = 2340;
    const uint8_t  INTERVALLE_MS   = 5;
    const uint8_t  VITESSE_CRUISE  = 80;
    const uint8_t  VITESSE_BOOST   = 180;
    uint16_t tempsEcoule = 0;
        
    pontH.tournerDroite(VITESSE_BOOST);
    _delay_ms(80);
    pontH.tournerDroite(VITESSE_CRUISE);
    
    bool enMouvement = true;

    while (tempsEcoule < DUREE_TOTALE_MS)
    {
        ci.lireDistance();

        if(ci.estObjetDetecte()){
            if(enMouvement){
                arreterMoteurs();
                enMouvement = false;
            }
            ci.incrementerPersonne(); 
            gererPoteau(del, ci);
            ci.resetEstUnePersonne();
            
            pontH.tournerDroite(VITESSE_BOOST);
            _delay_ms(80);
            pontH.tournerDroite(VITESSE_CRUISE);
            enMouvement = true;

        }
        else{
            if(!enMouvement){
                pontH.tournerDroite(VITESSE_BOOST);
                _delay_ms(80);
                pontH.tournerDroite(VITESSE_CRUISE);
                enMouvement = true;
            }
            del.allumerCouleur(Del::Couleur::VERT);
            tempsEcoule += INTERVALLE_MS;
            ci.incrementerPersonne();

        }
        _delay_ms(INTERVALLE_MS);
    }

    arreterMoteurs();
} 

void compterPersonnes() {} // B C compter tape

void entrerStationnementHoraire() 
{
    uint8_t placeStationnement; 
    CapteurLigne capteur; 
    Lecture l; 

    uint8_t nStationnement = l.getNumStationnement(); 

    if(capteur.estTropAGauchePrecis())
        placeStationnement++; 
        PontH::avancer(100);

    if(placeStationnement == nStationnement)
    {
        PontH::avancer(100);
        _delay_ms(250);
        PontH::tourner90DegresDroite(); 
        while(!(capteur.estSurLignePleine()))
        {
            PontH::avancer(100); 

        }
        PontH::arreter(); 

    }
    
    





}

void tournerDroite()
{
   CapteurLigne capteur;
   PontH::arreter();
   _delay_ms(1000);
   PontH::tourner90DegresDroite();    
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
                _delay_ms(2000);
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
                // scanner les personnes avec capteurInfra
                // prochain etat = COULOIR_NORD  
                scanPoteaux();
                etat = COULOIR_NORD;
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
