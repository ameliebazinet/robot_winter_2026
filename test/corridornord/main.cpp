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
    Del del(PORTC, PC6, PC7);
    PontH::initialiserRegistre();
    Etat etat = Etat::COULOIR;
    uint8_t nEntreeTrouver = 0 ; 

    PontH::avancer(255);
    _delay_ms(100);

    while (true) {
        switch (etat)
        {
            case Etat::COULOIR:
                if (capteur.estTropADroiteLarge()) {
                    // D4 et D5 actifs, trop près du mur, corriger à gauche
                    PontH::configurer(0, 100, 0, 110);
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
                    etat = Etat::VERIFICATION_ENTREE;
                }

                break;

            case Etat::VERIFICATION_ENTREE:
                PontH::tournerDroite(150);
                _delay_ms(150);
                PontH::arreter();
                _delay_ms(500);

                if (capteur.estTropADroite()) {
                    // Ligne retrouvée, c'était une déviation
                    etat = Etat::COULOIR;
                }
                else {
                    // Toujours pas de ligne, c'est une entrée
                    // Corriger le petit virage à droite
                    PontH::tournerGauche(150);
                    _delay_ms(150);
                    PontH::arreter();
                    etat = Etat::ENTREE_TROUVEE;
                }
                break;
            
            case Etat::ENTREE_TROUVEE:
                del.allumerCouleur(Del::Couleur::VERT);
                PontH::arreter();
                _delay_ms(1000);
                etat = Etat::FIN;
                break;

            case Etat::FIN:
                del.allumerCouleur(Del::Couleur::ETEINT);
                PontH::arreter();
                return 0;
        }
    }
}