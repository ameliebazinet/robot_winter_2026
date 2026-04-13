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
}

void tournerCouloirGauche()
{
    PontH::avancer(120);
    _delay_ms(1000);
    PontH::arreter();
    _delay_ms(500);
    PontH::tourner90DegresGauche();
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


            if (capteur.estTropADroite() || capteur.estAllumeMilieu()) {
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
            del.clignoterVert();
            return;
        }
    }
}

void executerSallesAD() {
    CapteurInfra ci;
    Del del(PORTC, PC6, PC7);
    PontH::initialiserRegistre();
    
    const uint16_t DUREE_TOTALE_MS = 2340;
    const uint8_t  INTERVALLE_MS   = 5;
    const uint8_t  VITESSE_CRUISE  = 80;
    const uint8_t  VITESSE_BOOST   = 180;
    uint16_t tempsEcoule = 0;
        
    PontH::tournerDroite(VITESSE_BOOST);
    _delay_ms(80);
    PontH::tournerDroite(VITESSE_CRUISE);
    
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
            
            PontH::tournerDroite(VITESSE_BOOST);
            _delay_ms(80);
            PontH::tournerDroite(VITESSE_CRUISE);
            enMouvement = true;

        }
        else{
            if(!enMouvement){
                PontH::tournerDroite(VITESSE_BOOST);
                _delay_ms(80);
                PontH::tournerDroite(VITESSE_CRUISE);
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

    recalibrerHoraire();
    while (true) {
        switch (etat)
        {
            case EtatCouloir::COULOIR:
                if (capteur.estTropADroiteLarge()) {
                    // D4 et D5 actifs, trop près du mur, corriger à gauche
                    PontH::configurer(0, 110, 0, 120);
                }
                else if (capteur.estTropADroite()) {
                    // D5 actif seulement, on suit bien la ligness
                    PontH::configurer(0, 110, 0, 115);
                }

                else if (capteur.estTropAGauche() || capteur.estTropAGaucheLarge())
                {
                    while(!(capteur.estTropADroite()))
                    {
                        PontH::tournerDroite(63);
                    }

                }
                else {
                    // D5 désactivé, possible entrée
                    PontH::arreter();
                    _delay_ms(500);
                    etat = EtatCouloir::VERIFICATION_ENTREE;
                }

                break;

            case EtatCouloir::VERIFICATION_ENTREE:
                PontH::tournerDroite(150);
                _delay_ms(200);
                PontH::arreter();
                _delay_ms(500);

                if (capteur.estTropADroite()) {
                    // Ligne retrouvée, c'était une déviation
                    etat = EtatCouloir::COULOIR;
                }
                else {
                    // Toujours pas de ligne, c'est une entrée
                    // Corriger le petit virage à droite
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
                 while(!(capteur.estAllumeCapteurQuelconque()))
                    PontH::avancer(128); 
                PontH::arreter(); 
                _delay_ms(1000); 
                //etat = EtatCouloir::FIN;
                return;

            // case EtatCouloir::FIN:
            //     del.allumerCouleur(Del::Couleur::ETEINT);
            //     PontH::arreter();
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
                recalibrerHoraire();
                suivreCouloir();
                tournerBoutCouloir(l);
                etat = COULOIR_NORD;
                break;
            }


            case COULOIR_NORD:
            {
                // roule jusqu'a porte de A,B,C,D
                // compteur part a 0
                // si compteur a 0 ou 3 on passe a PIECE_A_D
                // sinon compteur 1 ou 2 : PIECE_B_C
                // compteur++

                // quand compteur = 4 : rouler jusqua ligne pleine
                // virage 90
                // next State DERNIER_COULOIR_LONG
                couloirNord();
                compteurPiecesNord++; 
                
                if (compteurPiecesNord == 1 || compteurPiecesNord == 4) {
                    etat = PIECE_A_D;
                }

                else if (compteurPiecesNord == 2 || compteurPiecesNord == 3) {
                    etat = PIECE_B_C;
                }


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
