#include "execution.hpp"
#include "../lib/CapteurInfra.hpp"
#include "Del.hpp"
#include "../lecture/lecture.hpp"

Del del(PORTA, PC6, PC7);

void recalibrer()
{
    CapteurLigne capteur;
    while (!(capteur.estVide())) {
        if (capteur.estTropAGauchePrecis())
            PontH::tournerDroite(100);
        else if (capteur.estTropADroitePrecis())
            PontH::tournerGauche(100);
        else
            PontH::arreter();
    }
}

void suivreCouloir()
{
    CapteurLigne capteur;
    Lecture l;
    Del del(PORTC, PC6, PC7);
    PontH::initialiserRegistre();

    uint8_t nObstacles = 0;
    bool estSurObstacleAvant = false;    
    if (capteur.estSurLignePleine()) {
        return;
    }
    PontH::avancer(255);
    _delay_ms(100);

    recalibrer();

    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = capteur.estObstacleAuCentre();
        
        if (estSurObstacleMaintenant && !estSurObstacleAvant)
            nObstacles++;
        estSurObstacleAvant = estSurObstacleMaintenant;

        if (estSurObstacleMaintenant)
            del.allumerCouleur(Del::Couleur::ROUGE);
        else
            del.allumerCouleur(Del::Couleur::ETEINT);


        if (capteur.estTropADroitePrecis()) {
            PontH::configurer(0, 70, 0, 100);
        }
        else if (capteur.estTropAGauchePrecis()) {
            PontH::configurer(0, 100, 0, 70);
        }
        else {
            PontH::avancer(90);
        }
    }
    PontH::arreter();
    _delay_ms(250);

    if (l.getDirectionHoraire()) {
        tournerCorridorDroite();
    }
    else
        tournerCorridorGauche();

}

void sortirStationnementHoraire() 
{
    CapteurLigne capteur; 
    PontH::tourner180(); 
    PontH::arreter();
    _delay_ms(1000);

    while (!(capteur.estAllumeCapteurQuelconque())) {
        PontH::avancer(130);
    }

    PontH::arreter();
    _delay_ms(1000); 

    PontH::tournerDroite(150);
    while (!(capteur.estTropAGauchePrecis())) {}
    PontH::arreter();
    _delay_ms(1000);

    bool couloirTrouve = false;
    while (!couloirTrouve) {
        if (capteur.estTropADroitePrecis()) {
            PontH::configurer(0, 70, 0, 100);
            couloirTrouve = true;
            break;
        }
        
        else if (capteur.estTropAGauchePrecis()) {
            PontH::configurer(0, 130, 0, 70);
            _delay_ms(250);
        }

        else
            PontH::configurer(0, 80, 0, 110);
    }
    
    PontH::arreter();
    _delay_ms(500);
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
    _delay_ms(200);
    PontH::tournerGauche(100);
    _delay_ms(1000);

    PontH::arreter();
    _delay_ms(1000);

    bool couloirTrouve = false;
    while (!couloirTrouve) {
        if (capteur.estTropAGauche() || capteur.estTropAGauchePrecis() || capteur.estSurLignePleine()) {
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

void executerSallesAD() {
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
                PontH::arreter();
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

    PontH::arreter();
} 


void executerSallesBC(uint8_t& nObjetsLocal, volatile bool & tempsEcoule) // B C compter tape
{
    Communication c;
    c.initialisationUART();
    PontH::initialiserRegistre();

    // -- Commence quand la piece est detecter

    // tourne a droite/gauche de 90
    PontH::tourner90DegresDroite(); // ---
    PontH::arreter();
    _delay_ms(500);

    // avance de (temps requis) seconde en comptant le nombre de ligne parcouru. 
    uint32_t tempsMsParcoursBC = 2500;

    PontH::avancer(120);
    
    CapteurLigne cl;
    bool vuPrecedent = false;
    tempsEcoule = false;
    Minuterie::Minuterie1::partirMinuterie(tempsMsParcoursBC, Minuterie::A);
    while(!tempsEcoule)
    {
        bool vuActuel = !cl.estAllumeCapteurQuelconque();
        if (vuActuel && !vuPrecedent) nObjetsLocal++;
        vuPrecedent = vuActuel;
    }

    // apres (temps requis), quand tu rencontre une ligne. tourne de 180
    while(!cl.estSurLignePleine()) {}
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner180(); 
    PontH::arreter();
    _delay_ms(1000);

    // avance jusqu'a trouve le mur du fond du couloir (5 capteurs actifs)
    PontH::avancer(120);
    while(!cl.estSurLignePleine()) {}
    _delay_ms(600);
    PontH::arreter();
    _delay_ms(500);

    // tourne de 90 vers la gauche/droite
    PontH::tourner90DegresDroite(); // ---
    
} 

void tournerCorridorDroite()
{
    PontH::avancer(120);
    _delay_ms(600);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresDroite();
}

void tournerCorridorGauche()
{
    PontH::avancer(120);
    _delay_ms(600);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresGauche();
}

void faireExecution(uint8_t& nPersonnesLocalA,
                    uint8_t& nObjetsLocalB,
                    uint8_t& nObjetsLocalC,
                    uint8_t& nPersonnesLocalD,
                    uint8_t& nZonesEndommageesCouloirEst, 
                    uint8_t& nZonesEndommageesCouloirOuest,
                    volatile bool& tempsEcoule) 
{
    uint8_t compteurPiecesNord = 0;
    Etat etat = SORTIR_STATIONNEMENT;
    Lecture l;
    while (true) {
        switch (etat)
        {
            case SORTIR_STATIONNEMENT:
                if (l.getDirectionHoraire()) {
                    sortirStationnementHoraire();
                }
                else
                    sortirStationnementAntiHoraire();
                etat = COULOIRS_COTES;
                break;
            case COULOIRS_COTES:
                suivreCouloir();
                suivreCouloir();
                etat = COULOIR_NORD;
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
                executerSallesAD();
                etat = COULOIR_NORD;
                break;
            case PIECE_B_C:
                executerSallesBC(nObjetsLocalB, tempsEcoule);
                break;
            case ENTRER_STATIONNEMENT:
                
                // SI sens horaire : nb coches avant park = 5 - valeurPlaceParking
                // SI sens antihoraire : nb coches avant park = valeurPlaceParking
                break;
        }
    }
}
