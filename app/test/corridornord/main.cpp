// Test pour vérifier si le code de track des lignes marche.

#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include <util/delay.h>
#include "Del.hpp"

enum Etat {
    COULOIR,
    VERIFICATION_ENTREE,
    ENTREE_TROUVEE,
    FIN
};

int main()
{
    CapteurLigne capteur;
    Del del(PORTA, PA2, PA3);
    PontH::initialiserRegistre();
    Etat etat = Etat::COULOIR;

    PontH::avancer(255);
    _delay_ms(100);

    while (true) {
        switch (etat)
        {
            case Etat::COULOIR:
                if (!capteur.estActiveD4D5() && !capteur.estActiveD4D5()) {
                    while (!capteur.estActiveD4D5())
                        PontH::tournerDroite(130);
                }
                else if (!capteur.estActiveD4D5()) {
                    PontH::arreter();
                    etat = Etat::VERIFICATION_ENTREE;
                }
                else if (capteur.estActiveD4D5()) {
                    PontH::tournerGauche(75);
                }
                else {
                    PontH::configurer(0, 130, 0, 130);
                }
                break;

            case Etat::VERIFICATION_ENTREE :
                PontH::tournerDroite(150);
                _delay_ms(20);
                PontH::arreter();
                if (!capteur.estActiveD4D5()) {
                    etat = Etat::ENTREE_TROUVEE;
                }
                else if (capteur.estActiveD4D5()) {
                    etat = Etat::COULOIR;
                }
                break;
            
            case Etat::ENTREE_TROUVEE :
                del.allumerCouleur(Del::Couleur::VERT);
                PontH::arreter();
                _delay_ms(1000);
                etat = Etat::FIN;
                break;

            case Etat::FIN :
                del.allumerCouleur(Del::Couleur::ETEINT);
                PontH::arreter();
                return 0;
                break;
        }
    }
}