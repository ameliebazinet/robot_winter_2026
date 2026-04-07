#include "execution.hpp"
#include "../lib/CapteurInfra.hpp"
#include "Del.hpp"
#include "../lecture/lecture.hpp"

void suivreCouloir()
{
    CapteurLigne capteur;
    PontH::initialiserRegistre();

    PontH::avancer(255);
    _delay_ms(250);

    while (!capteur.estSurLignePleine()) {

        if (capteur.estTropADroite()) {
            PontH::configurer(1, 150, 1, 80);
        }

        else if (capteur.estTropAGauche()) {
            PontH::configurer(1, 80, 1, 150);
        }

        else {
            PontH::avancer(120);
        }

        _delay_ms(50);
    }
    PontH::arreter();
}

void longerLigneGauche()
{
    CapteurLigne capteur; 
    PontH::initialiserRegistre(); 


    while(!(capteur.estSurLignePleine())) {
        if(capteur.estTropAGauche()) {
            PontH::configurer(0,60,0,120);
        }
        else if (capteur.estTropADroite()){
            PontH::configurer(0,120,0,60);
        }

        else {

            PontH::avancer(110);
        }


    }
    PontH::arreter();

}

void longerLigneDroite()
{

        CapteurLigne capteur; 
    PontH::initialiserRegistre(); 


    while(!(capteur.estSurLignePleine() >= 0x0F )) {
        PontH::avancer(110);
        if(capteur.estTropADroite()) {
            PontH::configurer(0,95,0,105);
        }
        else {
            PontH::avancer(100); 
        }
    }
    PontH::arreter();

}

void sortirStationnementHorraire() 
{
    CapteurLigne capteur; 
    PontH::tourner180(); 
    PontH::arreter();
    _delay_ms(1000);


    while (!(capteur.estSurLignePleine()))
    {
        PontH::avancer(128);
    }
    PontH::arreter();
    _delay_ms(1000); 

    PontH::tourner90DegresDroite();
    PontH::arreter();
    _delay_ms(1000);


    // longerLigneGauche();
    // suivreCouloir();
}

void sortirStationnementAntiHorraire() 
{
    CapteurLigne capteur; 
    PontH::tourner180(); 
    PontH::arreter();
    _delay_ms(1000);


    while (!(capteur.estSurLignePleine()))
    {
        PontH::avancer(128);
    }
    PontH::arreter();
    _delay_ms(1000); 

    PontH::tourner90DegresGauche();
    PontH::arreter();
    _delay_ms(1000);
    while(!capteur.estSurLignePleine())
    {
        if(capteur.estTropADroite())
        PontH::configurer(0,60,0,120);

        else if (capteur.estTropADroitePrecis())
        {
            PontH::arreter();
            _delay_ms(1000);
            PontH::avancer(100);
            _delay_ms(1000);
        }

        else 
            PontH::configurer(0,80,0,60);
    
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

void arreterMoteurs()
{
    OCR0A = 0;
    OCR0B = 0;
    PORTB &= ~((1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5));
}

void clignoterVert(Del& del)
{
    for(uint8_t i = 0; i < 8; i++){
        del.allumerCouleur(Del::Couleur::VERT);
        _delay_ms(125);
        del.allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(125);
    }
}

void gererPoteau(Del& del, CapteurInfra& ci)
{
    while(true)
    {
        // A remplacer par son
        del.allumerCouleur(Del::Couleur::ROUGE);
        _delay_ms(500);
        del.allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(500);

        _delay_ms(2000);

        ci.lireDistance();
        if(!ci.estObjetDetecte()){
            clignoterVert(del);
            return;
        }
    }
}

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

void entrerStationnementHorraire() 
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
