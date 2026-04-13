#define F_CPU 8000000UL
#include "CapteurInfra.hpp"
#include "Communication.hpp"
#include "Del.hpp"
#include "../../modes/rapport.hpp"
#include "../../lecture/lecture.hpp"
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>

void clignoterVert(Del& del)
{
    
}


void attendreRetraitPoteau(Del& del, CapteurInfra& ci, Lecture& l)
{
    while(true) {
        for (uint8_t i = 0; i < 3; i++) {
            Son::jouer(l.getNote()[i]);
            _delay_ms(250);
            Son::arreter();
            _delay_ms(125);
        }
        _delay_ms(2000);

        ci.lireVoltage();
        if(!ci.estObjetDetecte()) {
            for(uint8_t i = 0; i < 8; i++) {
                del.allumerCouleur(Del::Couleur::VERT);
                _delay_ms(125);
                del.allumerCouleur(Del::Couleur::ETEINT);
                _delay_ms(125);
            }
        }
    }
}

int main()
{
    CapteurInfra ci;
    CapteurLigne cl;
    Lecture l;
    Del del(PORTC, PC6, PC7);
    Son::initialiserPiezo();
    PontH::initialiserRegistre();
    
    const uint16_t DUREE_TOTALE_MS = 600;
    const uint8_t  INTERVALLE_MS   = 5;
    const uint8_t  VITESSE_CRUISE  = 90;
    const uint8_t  VITESSE_BOOST   = 180;
    uint16_t tempsEcoule = 0;
    
    Communication com;
    com.initialisationUART();

    bool enMouvement = true;

    while (!cl.estTropADroite()) {
        ci.lireVoltage();
        // com.transmissionFormatee("adc: %d\r\n", ci.getVoltage());
        
    if(ci.estObjetDetecte()) {
            if(enMouvement) {
                PontH::arreter();
                enMouvement = false;
            }
            ci.incrementerPersonne(); 
            attendreRetraitPoteau(del, ci, l);
            ci.resetEstUnePersonne();
            
            PontH::tournerDroite(VITESSE_BOOST);
            _delay_ms(80);
            PontH::tournerDroite(VITESSE_CRUISE);
            enMouvement = true;

        }
        else {
            if(!enMouvement) {
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

    

    while(!cl.estTropAGauche())
        PontH::tournerGauche(100);
        
    com.transmissionFormatee("nb prsn: %d\r\n", ci.nPersonnes_);
    PontH::arreter();

   
}