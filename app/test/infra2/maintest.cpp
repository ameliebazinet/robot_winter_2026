#define F_CPU 8000000UL
#include "CapteurInfra.hpp"
#include "Communication.hpp"
#include "Del.hpp"
#include "../../modes/rapport.hpp"
#include "../../lecture/lecture.hpp"
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>

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

int main()
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
    com.transmissionFormatee("nb prsn: %d\r\n", ci.nPersonnes_);

    while (!cl.estTropAGauche())
        PontH::tournerGauche(VITESSE_SCAN);
        
    PontH::arreter();
}