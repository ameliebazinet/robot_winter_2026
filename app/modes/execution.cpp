#include "execution.hpp"


uint8_t compteurPiecesNord = 0; 
 
void recalibrer()
{
    CapteurLigne capteur;
    while (!capteur.estVide()) {
        if (capteur.estAllumeD4() || capteur.estTropADroite())
            PontH::tournerGauche(100);
        if (capteur.estAllumeD2() || capteur.estTropAGauche())
            PontH::tournerDroite(100);

    }
    PontH::arreter();
}

void recalibrerVirage(Lecture& l)
{
    CapteurLigne capteur;
    while (!(capteur.estVide())) {
        if (l.getDirectionHoraire()) {
            if (capteur.estTropADroite())
                PontH::tournerGauche(120);
            else if (capteur.estAllumeCapteurQuelconque())
                PontH::tournerDroite(120);
        }
        else {
            if (capteur.estTropAGauche())
                PontH::tournerDroite(120);
            else if (capteur.estAllumeCapteurQuelconque())
                PontH::tournerGauche(120);

        }
    }
}

void tournerCouloirDroite(Lecture& l)
{
    // PontH::accelererMax();
    // PontH::avancer(120);
    // _delay_ms(750);
    // PontH::arreter();
    // _delay_ms(500);
    // PontH::tourner90DegresDroite();
    // recalibrerVirage(l);
    
    CapteurLigne cl;
    while (!cl.estTropAGauche())
        PontH::tournerDroite(130);
    while (!cl.estTropAGauche())
        PontH::tournerDroite(120);
    PontH::arreter();
    _delay_ms(500);    
} 



void tournerCouloirGauche(Lecture& l) // A MODIFIER
{
    PontH::accelererMax();
    PontH::avancer(120);
    _delay_ms(750);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresGauche();
    recalibrerVirage(l);

}

void tournerBoutCouloir(Lecture& l)
{
    if (l.getDirectionHoraire()) {
    tournerCouloirDroite(l);
    }
    else
        tournerCouloirGauche(l);
}

void suivreCouloir()
{
    CapteurLigne capteur;
    Del del(PORTC, PC6, PC7);

    uint8_t nObstacles = 0;
    bool obstacleDejaCompte = false;
    uint8_t compteurSansObstacle = 0;

    recalibrer();

    PontH::accelererMax();

    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = capteur.estObstacleAuCentre();

        // Si on voit un obstacle
        if (estSurObstacleMaintenant) {
            compteurSansObstacle = 0;

            // On compte seulement si cet obstacle n'a pas déjà été compté
            if (!obstacleDejaCompte) {
                nObstacles++;
                obstacleDejaCompte = true;
            }
        }
        // Si on ne voit pas d'obstacle
        else {
            compteurSansObstacle++;

            // Il faut plusieurs lectures sans obstacle avant de considérer
            // que le robot est réellement sorti de l'obstacle
            if (compteurSansObstacle >= 3) {
                obstacleDejaCompte = false;
            }
        }

        if (estSurObstacleMaintenant && !capteur.estSurLignePleine())
            del.allumerCouleur(Del::Couleur::ROUGE);
        else
            del.allumerCouleur(Del::Couleur::ETEINT);

        if (capteur.estTropADroite())
            PontH::configurer(0, 80, 0, 110);
        else if (capteur.estTropAGauche())
            PontH::configurer(0, 110, 0, 80);
        else
            PontH::avancer(100);
    }

    del.allumerCouleur(Del::Couleur::ETEINT);
    _delay_ms(750);
    PontH::arreter();
    _delay_ms(500);
}

void sortirStationnement(Lecture& l)
{
    CapteurLigne capteur;
    bool horaire = l.getDirectionHoraire();

    PontH::tourner180();
    PontH::arreter();
    _delay_ms(1000);
    PontH::accelererMax();

    while (!capteur.estAllumeCapteurQuelconque()) {
        PontH::avancer(120);
    }
    _delay_ms(500);
    PontH::arreter();
    _delay_ms(500);

    if (horaire) {
        while (!capteur.estTropAGauche())
            PontH::tournerDroite(110);
    }
    else {
        while (!capteur.estTropADroite())
            PontH::tournerGauche(120);
    }
    
    PontH::arreter();
    _delay_ms(1000);

    PontH::accelererMax();

    while (!capteur.estSurLignePleine()) {
        if (horaire) {
            if (capteur.estTropAGauche() || capteur.estAllumeD2()) 
                PontH::configurer(0, 120, 0, 80);
            else
                PontH::configurer(0, 80, 0, 120);
        }
        else {
            if (capteur.estTropADroite() || capteur.estAllumeD4()) {
                PontH::configurer(0, 80, 0, 120);
                _delay_ms(100);
            }
            else
                PontH::configurer(0, 120, 0, 80);
        }
    } 
    _delay_ms(750); 
    PontH::arreter();
    _delay_ms(500);
}

void attendreRetraitPoteau(Del& del, CapteurInfra& ci, Lecture& l)
{
    while (true) {
        ci.lireVoltage();
        
        if (ci.estObjetDetecte()){

            for (uint8_t i = 69; i < 72; i++) {
                Son::jouer(i);
                _delay_ms(250);
                Son::arreter();
                _delay_ms(125);
            }
            _delay_ms(2000);
            
        }
        else{
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
    
    const uint8_t VITESSE_BOOST = 140;
    const uint8_t VITESSE_SCAN = 90;

    Communication com;
    com.initialisationUART();

    PontH::tournerDroite(VITESSE_BOOST);
    _delay_ms(500);
    PontH::arreter();
    _delay_ms(2000);
    PontH::accelererMax();

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

    PontH::reculer(140);
    _delay_ms(250);
    PontH::arreter();
    _delay_ms(250);

    PontH::tournerGauche(255);
    _delay_ms(150);

    while (!cl.estAllumeMilieu())
        PontH::tournerGauche(100);

    // PontH::arreter();
    // _delay_ms(250);
    
    while (!cl.estTropAGauche())
        PontH::tournerGauche(90);
      
    
    while (!cl.estVide())
        PontH::configurer(0, 140, 0, 80); // MODIFIE ICI

    PontH::arreter();
    _delay_ms(1000);
} 


void executerSallesBC(uint8_t& nObjetsLocal, volatile bool & tempsEcoule, Lecture& l) // B C compter tape
{
    Communication c;
    c.initialisationUART();
    PontH::initialiserRegistre();

    // tourne a droite/gauche de 90
    PontH::tournerDroite(255);
    _delay_ms(100);
    PontH::tournerDroite(120); 
    _delay_ms(800); // ---
    PontH::arreter();
    _delay_ms(500);

    // avance de (temps requis) seconde en comptant le nombre de ligne parcouru. 
    uint32_t tempsMsParcoursBC = 2000;

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
    while(!cl.estAllumeCapteurQuelconque()) {}
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner180();
    // PontH::tournerGauche(255);
    // _delay_ms(50);
    // PontH::tournerGauche(140);
    PontH::arreter();
    _delay_ms(1000);

    // avance jusqu'a trouve le mur du fond du couloir (5 capteurs actifs)
    PontH::accelererMax();
    PontH::avancer(120);
    while(!cl.estSurLignePleine()) {}
    _delay_ms(600);
    PontH::arreter();
    _delay_ms(500);

    // tourne de 90 vers la gauche/droite
    while (!cl.estTropAGauche())
        PontH::tournerDroite(120);            // MODIFIÉ ICI
    
    while (!cl.estTropAGauche())
        PontH::tournerDroite(120);
    PontH::arreter();
    _delay_ms(500);    

    Minuterie::Minuterie1::arreterMinuterie1();
} 

void entrerStationnementHoraire(Lecture& l) 
{
    uint8_t placeStationnement = l.getNumStationnement(); 
    CapteurLigne capteur; 
    bool temp = true;
    int8_t compteurStationnement = -1;

    recalibrer();
    PontH::accelererMax();

    // Phase 1 : se border / s'aligner avec estTropAGauche
    while (!capteur.estTropAGaucheLarge()) {
        if (capteur.estTropAGauche()) {
            PontH::configurer(0, 128, 0, 80);
        }
        else {
            PontH::configurer(0, 80, 0, 120);
        }
    }

    // Phase 2 : logique de comptage des places
    while (compteurStationnement != (int8_t)placeStationnement) {

        // Incrémentation place
        if (capteur.estTropAGaucheLarge()) {
            if (temp) {
                compteurStationnement++;
                temp = false;
            }
        }
        // correction
        else if (capteur.estTropAGauche()) {
            PontH::configurer(0, 120, 0, 90);
            temp = true;
        }
        // normal
        else {
            temp = true;
            PontH::configurer(0, 90, 0, 120);
        } 
    }

    PontH::arreter();
    _delay_ms(500);
    PontH::tournerDroite(255);
    _delay_ms(25);
    PontH::tourner90DegresDroite();
    _delay_ms(700);
    PontH::avancer(250);
    _delay_ms(200);
    PontH::avancer(110);

    while (!capteur.estSurLignePleine()) {}

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
    PontH::accelererMax();

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
        else {
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

void couloirNordHoraire()
{
    CapteurLigne capteur;
    Del del(PORTC, PC6, PC7);
    PontH::initialiserRegistre();
    EtatCouloir etat = EtatCouloir::COULOIR;

    recalibrer();
    _delay_ms(500);

    // PontH::accelererMax();

    // Tourner doucement à droite jusqu'à trouver D5
    while (!capteur.estTropADroite()) {
        PontH::tournerDroite(120);  // vitesse basse pour ne pas dépasser
    }
    // Dès que D5 est trouvé, si D4 aussi allumé, corriger un peu à gauche
    while (capteur.estAllumeD4()) {
        PontH::tournerGauche(110);
    }
    PontH::arreter();
    _delay_ms(250);

    PontH::accelererMax();
    PontH::accelererMax();

    
    while (true) {
        switch (etat)
        {
            case EtatCouloir::COULOIR:
                if (capteur.estAllumeD4()) {
                    // D4+D5 : trop près du mur, corriger à gauche
                    PontH::configurer(0,90,0, 120);
                }
                else if (capteur.estTropADroite()) {
                    // D5 seul : bien borné, avancer normalement
                    // PontH::avancer(110);
                    PontH::configurer(0,110,0,90);
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
                    PontH::configurer(0, 110, 0, 90);
                    etat = EtatCouloir::COULOIR;
                }
                else {
                    PontH::arreter();
                    _delay_ms(500);
                    etat = EtatCouloir::ENTREE_TROUVEE;
                }
                break;

            case EtatCouloir::ENTREE_TROUVEE:
                PontH::tournerGauche(150);
                _delay_ms(150);
                PontH::arreter();
                // while (!capteur.estTropAGauche()) {
                //     PontH::tournerGauche(110);
                // }
                // PontH::arreter();
                del.allumerCouleur(Del::Couleur::VERT);
                _delay_ms(1000);
                del.allumerCouleur(Del::Couleur::ETEINT);
                recalibrer();
                PontH::accelererMax();
                while (!capteur.estAllumeCapteurQuelconque()) {
                    PontH::configurer(0,100, 0, 115);//PontH::avancer(100);
                }
                _delay_ms(300);
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
    uint8_t compteurPiecesNord = 1; 
    Etat etat = COULOIR_NORD; 
    Lecture l;
    l.initialiserLecture();
    l.lireMemoire();
    while (true) {
        switch (etat)
        {
            case SORTIR_STATIONNEMENT:
            {
                sortirStationnement(l);
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
                couloirNordHoraire();
                compteurPiecesNord++; 
                
                if (compteurPiecesNord == 1 || compteurPiecesNord == 4)
                    etat = SALLE_A_D;

                else if (compteurPiecesNord == 2 || compteurPiecesNord == 3)
                    etat = SALLE_B_C;
                

                break;
            }

            case SALLE_A_D:
            {
                executerSallesAD();
                if (compteurPiecesNord < 4)
                    etat = COULOIR_NORD;
                else 
                    etat = DERNIER_COULOIR_COTE;

                break;
            }

            case SALLE_B_C:
            {
                executerSallesBC(nObjetsLocalB, tempsEcoule, l);
                if (compteurPiecesNord < 4)
                    etat = COULOIR_NORD;
                else 
                    etat = DERNIER_COULOIR_COTE;

                break;

            }

            case DERNIER_COULOIR_COTE :
                suivreCouloir();
                tournerBoutCouloir(l);
                suivreCouloir();
                tournerBoutCouloir(l);
                // for (uint8_t i = 69; i < 72; i++) {
                // Son::jouer(i);
                // _delay_ms(250);
                // Son::arreter();
                // _delay_ms(125);
                // }
                etat = ENTRER_STATIONNEMENT;
                break;

            case DERNIER_COULOIR_SUD : // a enlever
                suivreCouloir();
                etat = ENTRER_STATIONNEMENT;
                break;
            
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
