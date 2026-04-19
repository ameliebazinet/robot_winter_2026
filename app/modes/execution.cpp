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
    _delay_ms(500);
    CapteurLigne cl;
    if (l.getDirectionHoraire()) {
        PontH::tournerDroiteAccelere();
        while (!cl.estTropAGauche())
            PontH::tournerDroite(110);
    }
    else {
        PontH::tournerGaucheAccelere();
        while (!cl.estTropADroite())
            PontH::tournerGauche(110);
    }
    PontH::arreter();
    _delay_ms(500);
}

void suivreCouloir(uint8_t& nZones)
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
                nZones++;
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
            PontH::configurer(0, 90, 0, 130);
        else if (capteur.estTropAGauche())
            PontH::configurer(0, 130, 0, 90);
        else
            PontH::avancer(100);
    }

    del.allumerCouleur(Del::Couleur::ETEINT);
    _delay_ms(850);
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
        PontH::avancer(140);
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
            PontH::tournerGauche(120);
    }
    
    PontH::arreter();
    _delay_ms(1000);

    PontH::accelererMax();

    while (!capteur.estSurLignePleine()) {
        if (horaire) {
            if (capteur.estTropAGauche()) 
                PontH::configurer(0, 120, 0, 90);
            else
                PontH::configurer(0, 90, 0, 130);
        }
        else {
            if (capteur.estTropADroite())
                PontH::configurer(0, 80, 0, 140);
            else
                PontH::configurer(0, 110, 0, 100);
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

void executerSallesAD(uint8_t& nPersonnesLocal, Lecture& l)
{
    CapteurInfra ci;
    CapteurLigne cl;
    Del del(PORTC, PC6, PC7);
    Son::initialiserPiezo();
    PontH::initialiserRegistre();
    bool horaire = l.getDirectionHoraire();

    const uint8_t VITESSE_BOOST = 150;
    const uint8_t VITESSE_SCAN = 130; // modifie og 120

    Communication com;
    com.initialisationUART();

    if (horaire) {
        PontH::tournerDroiteAccelere();
        PontH::tournerDroite(VITESSE_BOOST);
    }
    else {
        PontH::tournerGaucheAccelere();
        PontH::tournerGauche(VITESSE_BOOST);
    }
    _delay_ms(250);
    PontH::arreter();
    _delay_ms(500);

    if (horaire) {
        while (!cl.estAllumeCapteurQuelconque()) {
            ci.lireVoltage();

            if (ci.estObjetDetecte()) {
                PontH::arreter();
                nPersonnesLocal++;
                attendreRetraitPoteau(del, ci, l);
            }
            else {
                PontH::tournerDroite(VITESSE_BOOST);
                _delay_ms(100);
                PontH::tournerDroite(VITESSE_SCAN);
                _delay_ms(75);
                PontH::arreter();
                _delay_ms(250);
            }
            _delay_ms(5);
        }

        PontH::arreter();
        PontH::tournerGaucheAccelere();
        PontH::tournerGauche(120);
        _delay_ms(250);
        PontH::reculerMax();
        PontH::reculer(120);
        _delay_ms(1000);
        PontH::arreter();
        _delay_ms(250);

        PontH::tournerGaucheAccelere();
        while (!cl.estAllumeMilieu())
            PontH::tournerGauche(100);
        while (!cl.estVide())
            PontH::tournerGauche(100);
    }

    else {
        while (!cl.estAllumeCapteurQuelconque()) {
            ci.lireVoltage();

            if (ci.estObjetDetecte()) {
                PontH::arreter();
                nPersonnesLocal++;
                attendreRetraitPoteau(del, ci, l);
            }
            else {
                PontH::tournerGauche(VITESSE_BOOST);
                _delay_ms(110);
                PontH::tournerGauche(VITESSE_SCAN);
                _delay_ms(75);
                PontH::arreter();
                _delay_ms(250);
            }
            _delay_ms(5);
        }

        PontH::arreter();
        PontH::tournerDroiteAccelere();
        PontH::tournerDroite(120);
        _delay_ms(250);
        PontH::reculerMax();
        PontH::reculer(120);
        _delay_ms(1000);
        PontH::arreter();
        _delay_ms(250);

        PontH::tournerDroiteAccelere();
        while (!cl.estAllumeMilieu())
            PontH::tournerDroite(100);
        while (!cl.estVide())
            PontH::tournerDroite(100);
    }

    PontH::arreter();
    _delay_ms(1000);
} 


void executerSallesBC(uint8_t& nObjetsLocal, volatile bool & tempsEcoule, Lecture& l, uint8_t compteurSalle)
{
    bool horaire = l.getDirectionHoraire();

    // tourne a droite/gauche de 90
    if (horaire) {
        PontH::tournerDroiteAccelere();
        PontH::tournerDroite(110);
        _delay_ms(800);  // og 900 modifie

    }
    else {
        PontH::tournerGaucheAccelere();
        PontH::tournerGauche(110);
        _delay_ms(900);
    }
    PontH::arreter();
    _delay_ms(500);
    PontH::reculerMax();

    PontH::reculer(120);
    _delay_ms(300);

    PontH::arreter();
    _delay_ms(500);


    // avance de (temps requis) seconde en comptant le nombre de ligne parcouru.
    uint32_t tempsMsParcourirBC;
    if (horaire)
        tempsMsParcourirBC = 2300; // og 2200 apres 2100 modifie
    else
        tempsMsParcourirBC = 2200;
    
    Del del(PORTC, PC6, PC7);

    del.allumerCouleur(Del::Couleur::VERT); // ligne test
    _delay_ms(1000);
    del.allumerCouleur(Del::Couleur::ETEINT);

    PontH::accelererMax(); 
    PontH::configurer(0, 90, 0, 100);

    CapteurLigne cl;
    
    bool vuPrecedent = true;
    
    Minuterie::Minuterie1::partirMinuterie(tempsMsParcourirBC, Minuterie::A);
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
    PontH::avancer(120);
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
            PontH::tournerGauche(100);
        while (!cl.estTropAGauche())
            PontH::tournerGauche(90);
    }
    PontH::arreter();
    _delay_ms(500);

    del.allumerCouleur(Del::Couleur::ETEINT); // ligne test
} 

void entrerStationnement(Lecture& l)
{
    Communication c;
    c.initialisationUART();
    _delay_ms(1000);
    

    uint8_t placeStationnement = l.getNumStationnement();
    CapteurLigne capteur;
    bool horaire = l.getDirectionHoraire();
    bool temp = true;

    recalibrer();
    PontH::accelererMax();
    recalibrer();

    

    if (horaire) {
        uint8_t compteur = 6;

        while (!capteur.estAllumeD2()) {
            if (capteur.estTropAGauche())
                PontH::configurer(0, 120, 0, 80);
            else
                PontH::configurer(0, 80, 0, 130);
        }

        while (compteur != (int8_t)placeStationnement) {
            if (capteur.estAllumeD2()) {
                if (temp) {
                    compteur--;
                    c.transmissionFormatee("%d \r\n", compteur);
                    temp = false;
                    PontH::configurer(0, 90, 0, 120);
                }
            }
            else if (capteur.estTropAGauche()) {
                PontH::configurer(0, 115, 0, 90);
                temp = true;
            }
            else {
                temp = true;
                PontH::configurer(0, 90, 0, 120);
            }
        }
    }
    else {
        int8_t compteur = -1;
    
        while (!capteur.estAllumeD4()) {
            if (capteur.estTropADroite())
                PontH::configurer(0, 80, 0, 130);
            else
                PontH::configurer(0, 100, 0, 80);
        }

        while (compteur != (int8_t)placeStationnement) {
            if (capteur.estAllumeD4()) {
                if (temp) {
                    compteur++;
                    temp = false;
                    PontH::configurer(0, 100, 0, 90);
                }
            }
            else if (capteur.estTropADroite()) {
                PontH::configurer(0, 80, 0, 130);
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
    _delay_ms(1000);

    PontH::accelererMax();
    PontH::configurer(0, 110, 0, 125);

    while (!capteur.estAllumeCapteurQuelconque()) {}

    PontH::arreter();
    _delay_ms(500);
    PontH::reculerMax();
    PontH::reculer(100);
    _delay_ms(500);
    PontH::arreter();

    // Son grave d'une seconde
    Minuterie::Minuterie1::arreterMinuterie1();
    Son::jouer(45); 
    _delay_ms(1000);
    Son::arreter();
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
                            PontH::tournerGauche(100);
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
                        PontH::configurer(0, 130, 0, 100);
                    }
                    else if (capteur.estTropAGauche()) {
                        // D1 seul : bien borné, avancer normalement
                        PontH::configurer(0, 100, 0, 130);
                    }
                    else if (capteur.estAllumeCapteurQuelconque())
                        PontH::tournerDroite(130);
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
                    PontH::tournerGauche(130);
                    _delay_ms(250);
                }
                else {
                    PontH::tournerDroite(140);
                    _delay_ms(250);
                }
                PontH::arreter();
                _delay_ms(500);

                PontH::accelererMax();
                if (horaire) 
                    PontH::configurer(0, 110, 0, 120);
                else    
                    PontH::configurer(0, 110, 0, 130);
                _delay_ms(2000); // a mmodifier og 1500

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
    bool horaire = l.getDirectionHoraire();
    while (true) {
        switch (etat)
        {
            case SORTIR_STATIONNEMENT:
            {
                sortirStationnement(l);
                tournerBoutCouloir(l);
                etat = COULOIR_COTE;
                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
                break;
            }

            case COULOIR_COTE:
            {
                // suivreCouloir(nZonesEndommageesCouloirOuest);
                suivreCouloir(horaire ? nZonesEndommageesCouloirOuest : nZonesEndommageesCouloirEst);

                tournerBoutCouloir(l);
                etat = COULOIR_NORD;
                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
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
                
                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
                break;
            }

            case SALLE_A_D:
            {
                if (compteurPiecesNord == 1)
                    executerSallesAD(horaire ? nPersonnesLocalA : nPersonnesLocalD, l);
                else
                    executerSallesAD(horaire ? nPersonnesLocalD : nPersonnesLocalA, l);
                if (compteurPiecesNord < 4)
                    etat = COULOIR_NORD;
                else 
                    etat = DERNIER_COULOIR_COTE;

                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
                break;
            }

            case SALLE_B_C:
            {
                if (compteurPiecesNord == 2)
                    executerSallesBC(horaire ? nObjetsLocalB : nObjetsLocalC, tempsEcoule, l, compteurPiecesNord);
                else 
                    executerSallesBC(horaire ? nObjetsLocalC : nObjetsLocalB, tempsEcoule, l, compteurPiecesNord);
                etat = COULOIR_NORD;
                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
                break;
            }

            case DERNIER_COULOIR_COTE :
                // suivreCouloir(nZonesEndommageesCouloirEst);
                suivreCouloir(horaire ? nZonesEndommageesCouloirOuest : nZonesEndommageesCouloirEst);

                tournerBoutCouloir(l);
                PontH::accelererMax();
                //suivreCouloir(nZonesEndommageesCouloirOuest);
                suivreCouloir(horaire ? nZonesEndommageesCouloirEst : nZonesEndommageesCouloirOuest);
                
                tournerBoutCouloir(l);
                etat = ENTRER_STATIONNEMENT;
                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
                break;
            
            case ENTRER_STATIONNEMENT:
                entrerStationnement(l);
                sauvegarderRapport( nPersonnesLocalA ,
                                    nObjetsLocalB,
                                    nObjetsLocalC,
                                    nPersonnesLocalD,
                                    nZonesEndommageesCouloirEst,
                                    nZonesEndommageesCouloirOuest);
                _delay_ms(1000);
                return;
        }
    }
}
