


// #define F_CPU 8000000UL
// #include "CapteurInfra.hpp"
// #include "Communication.hpp"
// #include "Del.hpp"
// #include "../../modes/rapport.hpp"
// #include "PontH.hpp"
// #include "CapteurLigne.hpp"
// #include <util/delay.h>

// void arreterMoteurs()
// {
//     OCR0A = 0;
//     OCR0B = 0;
//     PORTB &= ~((1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5));
// }

// void clignoterVert(Del& del)
// {
//     // 4 Hz pendant 2 secondes = 8 clignotements (on/off = 125ms chacun)
//     for(uint8_t i = 0; i < 8; i++){
//         del.allumerCouleur(Del::Couleur::VERT);
//         _delay_ms(125);
//          del.allumerCouleur(Del::Couleur::ETEINT);
//         _delay_ms(125);
//     }
// }

// void gererPoteau(Del& del, CapteurInfra& ci)
// {
//     while(true)
//     {
//         // Clignotement rouge unique
//         del.allumerCouleur(Del::Couleur::ROUGE);
//         _delay_ms(500);
//         del.allumerCouleur(Del::Couleur::ETEINT);
//         _delay_ms(500);

//         // Pause de 2 secondes
//         _delay_ms(2000);

//         // Vérifier si le poteau est encore là
//         ci.lireDistance();
//         if(!ci.estObjetDetecte()){
//             // Poteau retiré — clignoter vert 4Hz pendant 2s
//             clignoterVert(del);
//             return;
//         }
//         // Sinon on recommence la boucle
//     }
// }

// int main()
// {
//     CapteurInfra ci;
//     PontH pontH;
//     Del del(PORTA, PA0, PA1);
//     pontH.initialiserRegistre();
    
//     const uint16_t DUREE_TOTALE_MS = 2340;
//     const uint8_t  INTERVALLE_MS   = 5;
//     const uint8_t  VITESSE_CRUISE  = 80;
//     const uint8_t  VITESSE_BOOST   = 180;
//     uint16_t tempsEcoule = 0;
    
//     Communication com;
//     com.initialisationUART();
    
//     // Impulsion initiale
//     pontH.tournerDroite(VITESSE_BOOST);
//     _delay_ms(80);
//     pontH.tournerDroite(VITESSE_CRUISE);
    
//     bool enMouvement = true;

//     while (tempsEcoule < DUREE_TOTALE_MS)
//     {
//         ci.lireDistance();
//         com.transmissionFormatee("d: %d\r\n", ci.getDistance());

//         if(ci.estObjetDetecte()){
//             if(enMouvement){
//                 arreterMoteurs();
//                 enMouvement = false;
//             }
//             // Gérer le poteau — bloque jusqu'à ce qu'il soit retiré
//             gererPoteau(del, ci);
            
//             // Repartir après retrait du poteau
//             pontH.tournerDroite(VITESSE_BOOST);
//             _delay_ms(80);
//             pontH.tournerDroite(VITESSE_CRUISE);
//             enMouvement = true;
//         }
//         else{
//             if(!enMouvement){
//                 pontH.tournerDroite(VITESSE_BOOST);
//                 _delay_ms(80);
//                 pontH.tournerDroite(VITESSE_CRUISE);
//                 enMouvement = true;
//             }
//             del.allumerCouleur(Del::Couleur::VERT);
//             ci.incrementerPersonne();
//             tempsEcoule += INTERVALLE_MS;
            
//         }
        
//         _delay_ms(INTERVALLE_MS);
//     }

//     arreterMoteurs();
// }



#define F_CPU 8000000UL
#include "CapteurInfra.hpp"
#include "Communication.hpp"
#include "Del.hpp"
#include "../../modes/rapport.hpp"
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>

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

int main()
{
    CapteurInfra ci;
    PontH pontH;
    Del del(PORTA, PA0, PA1);
    pontH.initialiserRegistre();
    
    Communication com;
    com.initialisationUART();

    const uint16_t DUREE_TOTALE_MS = 2340;
    const uint8_t  INTERVALLE_MS   = 5;
    const uint8_t  VITESSE_CRUISE  = 80;
    const uint8_t  VITESSE_BOOST   = 180;
    uint16_t tempsEcoule = 0;
    

    const uint16_t DUREE_ROTATION_180_MS = 650;  // à calibrer
    const uint16_t DUREE_AVANCE_5CM_MS   = 300;  // à calibrer
    const uint8_t  VITESSE_ROTATION      = 120;
    const uint8_t  VITESSE_AVANCE        = 80;
  
    // tourner 180 droite
    pontH.tournerDroite(VITESSE_ROTATION);
    _delay_ms(DUREE_ROTATION_180_MS);
    arreterMoteurs();
    _delay_ms(100); // stabilisation

    // avancer 5cm
    pontH.avancer(VITESSE_AVANCE);   
    _delay_ms(DUREE_AVANCE_5CM_MS);
    arreterMoteurs();
    _delay_ms(100);

    // tourner 180 vers la gauche
    pontH.tournerGauche(VITESSE_ROTATION);
    _delay_ms(DUREE_ROTATION_180_MS);
    arreterMoteurs();
    _delay_ms(100);


// le scan en lui mm
    pontH.tournerDroite(VITESSE_BOOST);
    _delay_ms(80);
    pontH.tournerDroite(VITESSE_CRUISE);
    
    bool enMouvement = true;

    while (tempsEcoule < DUREE_TOTALE_MS)
    {
        ci.lireDistance();
        com.transmissionFormatee("d: %d\r\n", ci.getDistance());

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

    com.transmissionFormatee("nb prsn: %d\r\n", ci.nPersonnes_);
    arreterMoteurs();
}