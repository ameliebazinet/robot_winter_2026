#include "execution.hpp"


uint8_t compteurPiecesNord = 0; 
 
void recalibrerHoraire()
{
    CapteurLigne capteur;
    while (!(capteur.estVide())) {
        if (capteur.estTropADroite())
            PontH::tournerGauche(100);
        else if (capteur.estAllumeCapteurQuelconque()) 
            PontH::tournerDroite(100);
        else
            PontH::arreter();
    }
}

void tournerCouloirDroite()
{
    PontH::avancer(120);
    _delay_ms(1000);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresDroite();
    recalibrerHoraire();
}

void tournerCouloirGauche()
{
    PontH::avancer(120);
    _delay_ms(1000);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresGauche();
    recalibrerHoraire();

}

void tournerBoutCouloir(Lecture& l)
{
    if (l.getDirectionHoraire()) {
    tournerCouloirDroite();
    }
    else
        tournerCouloirGauche();

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


    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = capteur.estObstacleAuCentre();
        
        if (estSurObstacleMaintenant && !estSurObstacleAvant)
            nObstacles++;
        estSurObstacleAvant = estSurObstacleMaintenant;

        if (estSurObstacleMaintenant) {
            del.allumerCouleur(Del::Couleur::ROUGE);
            PontH::avancer(100); 
        }

        else
        {
            del.allumerCouleur(Del::Couleur::ETEINT);


            if (capteur.estTropADroite()) {
                PontH::configurer(0, 70, 0, 100);
            }
            else if (capteur.estTropAGauche()) {
                PontH::configurer(0, 100, 0, 70);
            }
            else {
                PontH::avancer(90);
            }


        }

    }
    PontH::arreter();
    _delay_ms(250);
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
    while (!(capteur.estTropAGauche())) {}
    PontH::arreter();
    _delay_ms(1000);

    bool couloirTrouve = false;
    while (!couloirTrouve) {
        if (capteur.estTropADroite()) {
            PontH::configurer(0, 70, 0, 100);
            couloirTrouve = true;
            break;
        }
        
        else if (capteur.estTropAGauche()) {
            PontH::configurer(0, 140, 0, 70);
            _delay_ms(250);
        }

        else
            PontH::configurer(0, 80, 0, 110);
    }
    
    PontH::arreter();
    _delay_ms(500);
}


void sortirStationnementAntihoraire() 
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

    PontH::tournerGauche(150);
    while (!(capteur.estTropADroite())) {}
    PontH::arreter();
    _delay_ms(1000);

    bool couloirTrouve = false;
    while (!couloirTrouve) {
        if (capteur.estTropAGauche()) {
            PontH::configurer(0, 100, 0, 70);
            couloirTrouve = true;
            break;
        }
        
        else if (capteur.estTropADroite()) {
            PontH::configurer(0, 70, 0, 130);
            _delay_ms(250);
        }

        else
            PontH::configurer(0, 110, 0, 80);
    }

    PontH::arreter();
    _delay_ms(500);

}

void attendreRetraitPoteau(Del& del, CapteurInfra& ci, Lecture& l)
{
    while (true) {
        for (uint8_t i = 0; i < 3; i++) {
            Son::jouer(l.getNote()[i]);
            _delay_ms(250);
            Son::arreter();
            _delay_ms(125);
        }
        _delay_ms(2000);

        ci.lireVoltage();
        if (!ci.estObjetDetecte()) {
            for (uint8_t i = 0; i < 8; i++) {
                del.allumerCouleur(Del::Couleur::VERT);
                _delay_ms(125);
                del.allumerCouleur(Del::Couleur::ETEINT);
                _delay_ms(125);
            }
            return;
        }
    }
}


void executerSallesAD() 
{
    CapteurInfra ci;
    CapteurLigne cl;
    Lecture l;
    Del del(PORTC, PC6, PC7);
    Son::initialiserPiezo();
    PontH::initialiserRegistre();
    
    const uint8_t VITESSE_BOOST = 150;
    const uint8_t VITESSE_SCAN = 95;

    Communication com;
    com.initialisationUART();

    PontH::tourner90DegresDroite();
    _delay_ms(500);

    PontH::tournerDroite(VITESSE_BOOST);
    _delay_ms(50);

    while (!cl.estTropADroite()) {
        ci.lireVoltage();

        if (ci.estObjetDetecte()) {
            PontH::arreter();
            ci.nPersonnes_++;
            attendreRetraitPoteau(del, ci, l);
            PontH::tournerDroite(VITESSE_BOOST);
            _delay_ms(50);
        }
        else {
            PontH::tournerDroite(VITESSE_SCAN);
        }

        _delay_ms(5);
    }

    PontH::arreter();

    while (!cl.estTropAGauche())
        PontH::tournerGauche(VITESSE_SCAN);
        
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

void entrerStationnementHoraire(Lecture& l) 
{
    uint8_t placeStationnement = l.getNumStationnement(); 
    CapteurLigne capteur; 
    bool temp = true;
    uint8_t compteurStationnement = 0; 
    PontH::avancer(255);
    _delay_ms(100);

    while(compteurStationnement != placeStationnement){

        // Incrementation place
        if(capteur.estTropAGaucheLarge() ) {
            if(temp){
                compteurStationnement++;
                temp = false;
            }
        }
        // correction
        else if(capteur.estTropAGauche()){
            PontH::configurer(0,120,0,90);
            temp = true;
        }
        // normal
        else{
            temp = true;
            PontH::configurer(0,90,0,110);
        } 
    }

    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresDroite();
    _delay_ms(700);
    PontH::avancer(250);
    _delay_ms(200);
    PontH::avancer(110);
    while(!capteur.estSurLignePleine()){}
    PontH::arreter();
    _delay_ms(500);
    PontH::reculer(150);
    _delay_ms(500);
    PontH::arreter();
}
void entrerStationnementAntihoraire(Lecture& l) 
{
    uint8_t placeStationnement = l.getNumStationnement(); 
    CapteurLigne capteur; 
    bool temp = true;
    uint8_t compteurStationnement = 5; 
    PontH::avancer(255);
    _delay_ms(100);

    while(compteurStationnement != placeStationnement){

        if(capteur.estTropADroiteLarge()) {
            if(temp){
                compteurStationnement--;
                temp = false;
            }
        }
        else if(capteur.estTropADroite()){
            PontH::configurer(0,90,0,120);
            temp = true;
        }
        else{
            temp = true;
            PontH::configurer(0,110,0,90);
        } 
    }

    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresGauche();
    _delay_ms(700);
    PontH::avancer(250);
    _delay_ms(200);
    PontH::avancer(110);
    while(!capteur.estSurLignePleine()){}
    PontH::arreter();
    _delay_ms(500);
    PontH::reculer(150);
    _delay_ms(500);
    PontH::arreter();
}

void couloirNord()
{
    CapteurLigne capteur;
    Del del(PORTC, PC6, PC7);
    PontH::initialiserRegistre();
    EtatCouloir etat = EtatCouloir::COULOIR;

    PontH::avancer(255);
    _delay_ms(100);

    // Tourner doucement à droite jusqu'à trouver D5
    while (!capteur.estTropADroite()) {
        PontH::tournerDroite(70);  // vitesse basse pour ne pas dépasser
    }
    // Dès que D5 est trouvé, si D4 aussi allumé, corriger un peu à gauche
    while (capteur.estTropADroiteLarge()) {
        PontH::tournerGauche(70);
    }
    PontH::arreter();
    _delay_ms(200);
    PontH::avancer(255);
    _delay_ms(100);
    while (true) {
        switch (etat)
        {
            case EtatCouloir::COULOIR:
                if (capteur.estTropADroiteLarge()) {
                    // D4+D5 : trop près du mur, corriger à gauche
                    PontH::configurer(0, 90, 0, 120);
                }
                else if (capteur.estTropADroite()) {
                    // D5 seul : bien borné, avancer normalement
                    PontH::avancer(110);
                }
                else if (capteur.estTropAGauche()) {
                    // D1 : trop loin du mur, corriger à droite
                    PontH::configurer(0, 120, 0, 90);
                }
                else {
                    // Aucun capteur latéral : possible entrée
                    PontH::arreter();
                    _delay_ms(300);
                    etat = EtatCouloir::VERIFICATION_ENTREE;
                }
                break;

            case EtatCouloir::VERIFICATION_ENTREE:
                PontH::tournerDroite(150);
                _delay_ms(150);
                PontH::arreter();
                _delay_ms(300);

                if (capteur.estTropADroite()) {
                    PontH::avancer(255);
                    _delay_ms(100);
                    etat = EtatCouloir::COULOIR;
                }
                else {
                    PontH::tournerGauche(150);
                    _delay_ms(150);
                    PontH::arreter();
                    etat = EtatCouloir::ENTREE_TROUVEE;
                }
                break;

            case EtatCouloir::ENTREE_TROUVEE:
                del.allumerCouleur(Del::Couleur::VERT);
                PontH::arreter();
                _delay_ms(1000);
                del.allumerCouleur(Del::Couleur::ETEINT);
                while (!capteur.estAllumeCapteurQuelconque())
                    PontH::avancer(128);
                PontH::arreter();
                _delay_ms(1000);
                return;
        }
    }
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
            {
                if (l.getDirectionHoraire()) {
                    sortirStationnementHoraire();
                }
                else
                    sortirStationnementAntihoraire();
                etat = PREMIER_COULOIR_SUD;
                break;

            }

            case PREMIER_COULOIR_SUD :
            {
                suivreCouloir();
                tournerBoutCouloir(l);
                etat = COULOIR_COTE;
                break; 
            }


            case COULOIR_COTE:
            {
                suivreCouloir();
                tournerBoutCouloir(l);
                etat = COULOIR_NORD;
                break;
            }


            case COULOIR_NORD:
            {
                couloirNord();
                compteurPiecesNord++; 
                
                if (compteurPiecesNord == 1 || compteurPiecesNord == 4)
                    etat = PIECE_A_D;

                else if (compteurPiecesNord == 2 || compteurPiecesNord == 3)
                    etat = PIECE_B_C;

                break;
            }

            case PIECE_A_D:
            {
                executerSallesAD();
                if (compteurPiecesNord < 4)
                    etat = COULOIR_NORD;
                else 
                    etat = DERNIER_COULOIR_SUD;

                break;
            }

            case PIECE_B_C:
            {
                executerSallesBC(nObjetsLocalB, tempsEcoule);
                if (compteurPiecesNord < 4)
                    etat = COULOIR_NORD;
                else 
                    etat = DERNIER_COULOIR_SUD;

                break;

            }

            case ENTRER_STATIONNEMENT:
                if (l.getDirectionHoraire()) {
                    entrerStationnementHoraire(l);
                }
                else
                    entrerStationnementAntihoraire(l);
                return;
        }
    }
}
