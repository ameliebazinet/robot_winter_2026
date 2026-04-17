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

void tournerBoutCouloir(Lecture& l)
{
    CapteurLigne cl;
    if (l.getDirectionHoraire()) {
        PontH::tournerDroiteAccelere();
        while (!cl.estTropAGauche())
            PontH::tournerDroite(110);
        while (!cl.estTropAGauche())
            PontH::tournerDroite(110);
    }
    else {
        PontH::tournerGaucheAccelere();
        while (!cl.estTropADroite())
            PontH::tournerGauche(110);
        while (!cl.estTropADroite())
            PontH::tournerGauche(110);
    }
    PontH::arreter();
    _delay_ms(500);
}

void suivreCouloir()
{
    CapteurLigne capteur;
    Del del(PORTC, PC6, PC7);

    uint8_t nObstacles = 0;
    bool obstacleDejaCompte = false;
    uint8_t compteurSansObstacle = 0;
    uint8_t compteurAvecObstacle = 0;

    recalibrer();

    PontH::accelererMax();

    while (!capteur.estSurLignePleine()) {
        bool estSurObstacleMaintenant = capteur.estObstacleAuCentre();

        // Si on voit un obstacle
        if (estSurObstacleMaintenant) {
            compteurSansObstacle = 0;
            compteurAvecObstacle++;
            _delay_ms(50);

            // Il faut plusieurs lectures avec obstacle pour confirmer
            // qu'un obstacle est véritablement là
            if (compteurAvecObstacle >= 3 && !obstacleDejaCompte) {
                nObstacles++;
                obstacleDejaCompte = true;
            }
        }
        // Si on ne voit pas d'obstacle
        else {
            compteurAvecObstacle = 0;
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
            PontH::configurer(0, 90, 0, 120);
        else if (capteur.estTropAGauche())
            PontH::configurer(0, 120, 0, 90);
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

    PontH::accelererMax();
    while (!capteur.estAllumeCapteurQuelconque())
        PontH::avancer(120);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner180();
    _delay_ms(1000);

    PontH::accelererMax();
    while (!capteur.estAllumeCapteurQuelconque()) {
        PontH::avancer(120);
    }

    _delay_ms(500);
    PontH::arreter();
    _delay_ms(500);

    if (horaire) {
        PontH::tournerDroiteAccelere();
        while (!capteur.estTropAGauche())
            PontH::tournerDroite(90);
    }

    else {
        PontH::tournerGaucheAccelere();
        while (!capteur.estTropADroite())
            PontH::tournerGauche(90);
    }
    
    PontH::arreter();
    _delay_ms(1000);

    PontH::accelererMax();

    while (!capteur.estSurLignePleine()) {
        if (horaire) {
            if (capteur.estTropAGauche() || capteur.estAllumeD2()) 
                PontH::configurer(0, 120, 0, 90);
            else
                PontH::configurer(0, 90, 0, 130);
        }
        else {
            if (capteur.estTropADroite() || capteur.estAllumeD4())
                PontH::configurer(0, 90, 0, 120);
            else
                PontH::configurer(0, 130, 0, 90);
        }
    } 
    _delay_ms(750); 
    PontH::arreter();
    _delay_ms(500);
}

void attendreRetraitPoteau(Del& del, CapteurInfra& ci, Lecture& l)
{
    while (true) {
        // Confirmer 3 lectures consécutives avant de décider
        uint8_t lecturesObstacle = 0;
        for (uint8_t i = 0; i < 3; i++) {
            ci.lireVoltage();
            if (ci.estObjetDetecte()) lecturesObstacle++;
            _delay_ms(10);
        }

        if (lecturesObstacle >= 2) {
            for (uint8_t i = 0; i < TAILLE_TABLEAU_NOTE; i++) {
                Son::jouer(l.getNote()[i]);
                _delay_ms(250);
                Son::arreter();
                _delay_ms(125);
            }
            _delay_ms(2000);
        }
        else {
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

void executerSallesAD(Lecture& l)
{
    CapteurInfra ci;
    CapteurLigne cl;
    Del del(PORTC, PC6, PC7);
    Son::initialiserPiezo();
    PontH::initialiserRegistre();
    bool horaire = l.getDirectionHoraire();

    const uint8_t VITESSE_BOOST = 150;
    const uint8_t VITESSE_SCAN = 120; // modifie og 120

    Communication com;
    com.initialisationUART();

    if (horaire) {
        PontH::tournerDroite(VITESSE_BOOST);
    }
    else {
        PontH::tournerGauche(VITESSE_BOOST);
    }
    _delay_ms(250); // modifie og 250
    PontH::arreter();
    _delay_ms(500);

    if (horaire) {
        while (!cl.estAllumeCapteurQuelconque()) {
            ci.lireVoltage();

            if (ci.estObjetDetecte()) {
                PontH::arreter();
                ci.nPersonnes_++;
                attendreRetraitPoteau(del, ci, l);
            }
            else {
                PontH::tournerDroite(VITESSE_BOOST);
                _delay_ms(50);
                PontH::tournerDroite(VITESSE_SCAN);
                _delay_ms(75); // modifie
                PontH::arreter();
                _delay_ms(500);
            }
            _delay_ms(5);
        }
    }
    else {
        while (!cl.estAllumeCapteurQuelconque()) {
            ci.lireVoltage();

            if (ci.estObjetDetecte()) {
                PontH::arreter();
                ci.nPersonnes_++;
                attendreRetraitPoteau(del, ci, l);
                PontH::tournerGauche(VITESSE_BOOST);
                _delay_ms(50);
            }
            else {
                PontH::tournerDroite(VITESSE_BOOST);
                _delay_ms(50);
                PontH::tournerGauche(VITESSE_SCAN);
                _delay_ms(100);
                PontH::arreter();
                _delay_ms(500);
            }
            _delay_ms(5);
        }
    }

    PontH::arreter();

    PontH::reculer(140);
    _delay_ms(500); // modifie og 100
    PontH::arreter();
    _delay_ms(250);

    if (horaire) {
        PontH::tournerGaucheAccelere();

        while (!cl.estAllumeMilieu())
            PontH::tournerGauche(100);

        // while (!cl.estTropAGauche())
        //     // PontH::tournerGauche(90);
        //     PontH::configurer(1, 90, 0, 115);

        while (!cl.estVide())
            PontH::configurer(0, 110, 0, 80);
    }
    else {
        PontH::tournerDroiteAccelere();

        while (!cl.estAllumeMilieu())
            PontH::tournerDroite(100);

        // while (!cl.estTropADroite())
        //     PontH::configurer(0, 115, 1, 90);

        while (!cl.estVide())
            PontH::configurer(0, 80, 0, 110);
    }

    PontH::arreter();
    _delay_ms(1000);
} 


void executerSallesBC(uint8_t& nObjetsLocal, volatile bool & tempsEcoule, Lecture& l, uint8_t compteurSalle)
{
    PontH::initialiserRegistre();
    bool horaire = l.getDirectionHoraire();

    // tourne a droite/gauche de 90
    if (horaire) {
        PontH::tournerDroiteAccelere();
        PontH::tournerDroite(110);
    }
    else {
        PontH::tournerGaucheAccelere();
        PontH::tournerGauche(110);
    }
    _delay_ms(700);
    PontH::arreter();
    _delay_ms(500);
    PontH::reculerMax();

    PontH::reculer(110);
    _delay_ms(300);

    PontH::arreter();
    _delay_ms(500);


    // avance de (temps requis) seconde en comptant le nombre de ligne parcouru.
    uint32_t tempsMsParcoursBC = 2000; 
    Del del(PORTC, PC6, PC7);

    del.allumerCouleur(Del::Couleur::VERT); // ligne test
    _delay_ms(1000);
    del.allumerCouleur(Del::Couleur::ETEINT);

    PontH::accelererMax(); 
    PontH::configurer(0, 90, 0, 95);

    CapteurLigne cl;
    
    bool vuPrecedent = false;
    
    Minuterie::Minuterie1::partirMinuterie(tempsMsParcoursBC, Minuterie::A);
    tempsEcoule = false;  // reset APRES avoir arme le timer, pour eviter race condition avec ancienne minuterie

    while(!tempsEcoule)
    {
        bool vuActuel = !cl.estAllumeCapteurQuelconque();
        if (vuActuel && !vuPrecedent) nObjetsLocal++;
        vuPrecedent = vuActuel;

        if (!vuActuel)
            del.allumerCouleur(Del::Couleur::ROUGE);
        else
            del.allumerCouleur(Del::Couleur::ETEINT);
    }
    PontH::arreter();
    del.allumerCouleur(Del::Couleur::VERT); // ligne test
    _delay_ms(1000);
    del.allumerCouleur(Del::Couleur::ETEINT);
    //_delay_ms(1000);

    // Continuer jusqu'au fond de la salle (ligne pleine = mur du fond, pas un obstacle)
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner180();
    _delay_ms(1000);

    // avance jusqu'a trouve le mur du fond du couloir
    PontH::accelererMax(); 
    PontH::avancer(100);
    // while(!cl.estAllumeCapteurQuelconque()) {}
    while(!cl.estTroisCapteursActifs()) {}
    _delay_ms(750);
    PontH::arreter();
    _delay_ms(500);

    // tourne de 90 vers la gauche/droite
    if (horaire) {
        PontH::tournerDroiteAccelere();   // <-- boost ajouté
        while (!cl.estTropAGauche())
            PontH::tournerDroite(90);
        while (!cl.estTropADroite())
            PontH::tournerDroite(80);
    }
    else {
        PontH::tournerGaucheAccelere();   // <-- boost ajouté
        while (!cl.estTropADroite())
            PontH::tournerGauche(90);
        while (!cl.estTropAGauche())
            PontH::tournerGauche(80);
    }
    PontH::arreter();
    _delay_ms(500);

    del.allumerCouleur(Del::Couleur::ETEINT); // ligne test
} 


void entrerStationnement(Lecture& l)
{
    uint8_t placeStationnement = l.getNumStationnement();
    CapteurLigne capteur;
    bool horaire = l.getDirectionHoraire();
    bool temp = true;

    recalibrer();
    PontH::accelererMax();
    recalibrer();

    if (horaire) {
        int8_t compteur = -1;

        while (!capteur.estTropAGaucheLarge()) {
            if (capteur.estTropAGauche())
                PontH::configurer(0, 128, 0, 80);
            else
                PontH::configurer(0, 80, 0, 120);
        }

        while (compteur != (int8_t)placeStationnement) {
            if (capteur.estTropAGaucheLarge()) {
                if (temp) {
                    compteur++;
                    temp = false;
                }
            }
            else if (capteur.estTropAGauche()) {
                PontH::configurer(0, 120, 0, 90);
                temp = true;
            }
            else {
                temp = true;
                PontH::configurer(0, 90, 0, 120);
            }
        }
    }
    else {
        uint8_t compteur = 6;
        while (compteur != placeStationnement) {
            if (capteur.estTropADroiteLarge()) {
                if (temp) {
                    compteur--;
                    temp = false;
                }
            }
            else if (capteur.estTropADroite()) {
                PontH::configurer(0, 90, 0, 120);
                temp = true;
            }
            else {
                temp = true;
                PontH::configurer(0, 110, 0, 90);
            }
        }
    }

    PontH::avancer(128);
    _delay_ms(250);
    PontH::arreter();
    _delay_ms(500);

    if (horaire) {
        PontH::tourner90DegresDroite();
    }
    else {
        PontH::tourner90DegresGauche();
    }

    _delay_ms(500);
    PontH::avancer(250);
    _delay_ms(200);
    PontH::avancer(110);

    while (!capteur.estSurLignePleine()) {}

    PontH::arreter();
    _delay_ms(500);
    PontH::reculer(250);
    _delay_ms(500);
    PontH::arreter();

}

void couloirNord(Lecture& l)
{
    CapteurLigne capteur;
    Del del(PORTC, PC6, PC7);
    PontH::initialiserRegistre();
    EtatCouloir etat = EtatCouloir::COULOIR;
    bool horaire = l.getDirectionHoraire();

    recalibrer();

    if (horaire) { // modifie ici
        // Tourner doucement à droite jusqu'à trouver D5
        while (!capteur.estTropADroite())
            PontH::configurer(0, 130, 0, 90);
    }
    else {
        // Tourner doucement à gauche jusqu'à trouver D1
        while (!capteur.estTropAGauche())
            PontH::configurer(0, 90, 0, 130);
    }

    PontH::arreter();
    _delay_ms(250);
    PontH::accelererMax();

    while (true) {
        switch (etat)
        {
            case EtatCouloir::COULOIR:
                if (horaire) {
                    if (capteur.estAllumeD4()) {
                        // D4+D5 : trop près du mur, corriger à gauche
                        PontH::configurer(0, 90, 0, 120);
                    }
                    else if (capteur.estTropADroite()) {
                        // D5 seul : bien borné, avancer normalement
                        PontH::configurer(0, 110, 0, 90);
                    }
                    else if (capteur.estAllumeCapteurQuelconque()) {
                            PontH::tournerGauche(120);
                    }
                    else {
                        // Aucun capteur latéral : possible entrée
                        PontH::arreter();
                        _delay_ms(300);
                        etat = EtatCouloir::VERIFICATION_ENTREE;
                    }
                }
                else {
                    if (capteur.estAllumeD2()) {
                        // D1+D2 : trop près du mur, corriger à droite
                        PontH::configurer(0, 120, 0, 90);
                    }
                    else if (capteur.estTropAGauche()) {
                        // D1 seul : bien borné, avancer normalement
                        PontH::configurer(0, 90, 0, 120);
                    }
                    else if (capteur.estAllumeCapteurQuelconque())
                        PontH::tournerDroite(120);
                    else {
                        // Aucun capteur latéral : possible entrée
                        PontH::arreter();
                        _delay_ms(300);
                        etat = EtatCouloir::VERIFICATION_ENTREE;
                    }
                }
                break;

            case EtatCouloir::VERIFICATION_ENTREE:
                if (horaire) {
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
                }
                else {
                    PontH::tournerGauche(150);
                    _delay_ms(150);
                    PontH::arreter();
                    _delay_ms(300);

                    if (capteur.estTropAGauche()) {
                        PontH::configurer(0, 90, 0, 110);
                        etat = EtatCouloir::COULOIR;
                    }
                    else {
                        PontH::arreter();
                        _delay_ms(500);
                        etat = EtatCouloir::ENTREE_TROUVEE;
                    }
                }
                break;

            case EtatCouloir::ENTREE_TROUVEE:
                if (horaire) {
                    PontH::tournerGauche(150);
                }
                else {
                    PontH::tournerDroite(150);
                }
                _delay_ms(250); // modifie og 150
                PontH::arreter();
                _delay_ms(500);

                PontH::accelererMax();
                if (horaire) 
                    PontH::configurer(0, 110, 0, 120);
                else    
                    PontH::configurer(0, 120, 0, 110);
                _delay_ms(1500);

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
                couloirNord(l);
                compteurPiecesNord++; 
                
                if (compteurPiecesNord == 1 || compteurPiecesNord == 4)
                    etat = SALLE_A_D;

                else if (compteurPiecesNord == 2 || compteurPiecesNord == 3)
                    etat = SALLE_B_C;
                

                break;
            }

            case SALLE_A_D: // modifie if statement : pas dernier couloir dans bc et nobjets local b different de nobjets local a
            {
                executerSallesAD(l);
                if (compteurPiecesNord < 4)
                    etat = COULOIR_NORD;
                else 
                    etat = DERNIER_COULOIR_COTE;
                break;
            }

            case SALLE_B_C:
            {
                if (compteurPiecesNord == 2)
                    executerSallesBC(nObjetsLocalB, tempsEcoule, l, compteurPiecesNord);
                else 
                    executerSallesBC(nObjetsLocalC, tempsEcoule, l, compteurPiecesNord);
                etat = COULOIR_NORD;
                break;
            }

            case DERNIER_COULOIR_COTE :
                suivreCouloir();
                tournerBoutCouloir(l);
                PontH::accelererMax(); 
                suivreCouloir();
                tournerBoutCouloir(l);
                etat = ENTRER_STATIONNEMENT;
                break;

            case DERNIER_COULOIR_SUD :
                suivreCouloir();
                etat = ENTRER_STATIONNEMENT;
                break;
            
            case ENTRER_STATIONNEMENT:
                entrerStationnement(l);
                return;
        }
    }
}
