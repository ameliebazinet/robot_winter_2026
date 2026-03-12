#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "InterruptionExterne.hpp"
#include "Del.hpp"

/* enum class State
{
    INIT, 
    PRESS_ONE,
    PRESS_TWO,
    PRESS_FINAL,
    OFF_ONE,
    OFF_TWO,
    OFF_FINAL
};

volatile bool interruptionBouton = false;

ISR(INT0_vect)
{
    interruptionBouton = true;
}

int main()
{

    Del del(PORTA, PA0, PA1);
    InterruptionExterne interruption;

    State currentState = State::INIT;

    interruption.initialisation(0, 1);

    while (true)
    {
        switch (currentState)
        {
            case State::INIT:
                del.allumerCouleur(Del::Couleur::VERT);
                if (interruptionBouton)
                {
                    _delay_ms(10);
                    interruptionBouton = false;

                    if (interruption.lireEtatBroche(0))
                    {
                        currentState = State::OFF_ONE;
                    }
                }
                break;

            case State::OFF_ONE:
                del.allumerCouleur(Del::Couleur::ROUGE);
                if (interruptionBouton)
                {
                    _delay_ms(10);
                    interruptionBouton = false;

                    if (!interruption.lireEtatBroche(0))
                    {
                        currentState = State::PRESS_ONE;
                    }
                }
                break;

            case State::PRESS_ONE:
                del.allumerCouleur(Del::Couleur::ETEINT);
                if (interruptionBouton)
                {
                    _delay_ms(10);
                    interruptionBouton = false;

                    if (interruption.lireEtatBroche(0))
                    {
                        currentState = State::OFF_TWO;
                    }
                }
                break;

            case State::OFF_TWO:
                del.allumerCouleur(Del::Couleur::VERT);
                if (interruptionBouton)
                {
                    _delay_ms(10);
                    interruptionBouton = false;

                    if (!interruption.lireEtatBroche(0))
                    {
                        currentState = State::PRESS_TWO;
                    }
                }
                break;

            case State::PRESS_TWO:
                del.allumerCouleur(Del::Couleur::ROUGE);
                if (interruptionBouton)
                {
                    _delay_ms(10);
                    interruptionBouton = false;

                    if (interruption.lireEtatBroche(0))
                    {
                        currentState = State::OFF_FINAL;
                    }
                }
                break;

            case State::OFF_FINAL:
                del.allumerCouleur(Del::Couleur::ETEINT);
                if (interruptionBouton)
                {
                    _delay_ms(10);
                    interruptionBouton = false;

                    if (!interruption.lireEtatBroche(0))
                    {
                        currentState = State::PRESS_FINAL;
                    }
                }
                break;

            case State::PRESS_FINAL:
                del.allumerCouleur(Del::Couleur::VERT);
                _delay_ms(2000);
                currentState = State::INIT;
                break;
        }
    }ß

    return 0;
}

 */
/*     const uint16_t LUMIERE_FAIBLE = 0xA0;
    const uint16_t LUMIERE_FORTE = 0xF0;  
    
    can convertisseur;
    Del del(PORTB, PB0, PB1);

    uint8_t DELAI_LED = 10;
    while (true) {
        uint16_t valeurLumiere = convertisseur.lecture(0) >> 2;

        if (valeurLumiere < LUMIERE_FAIBLE) {
            del.allumerCouleur(Del::Couleur::VERT);
            _delay_ms(DELAI_LED);
        }

        else if (valeurLumiere > LUMIERE_FORTE) {
            del.allumerCouleur(Del::Couleur::ROUGE);
            _delay_ms(DELAI_LED);
        }

        else {
            del.allumerCouleurAmbre();
        }

    } */
    
/*     Communication comm;
    comm.initialisationUART();

    while (1)
    {
        while (1)
        {
            uint8_t etat = 3;
            DEBUG_PRINT(comm, "HSAHAHAA\n");
            DEBUG_PRINT(comm, "Val: %d et %d\n", etat, 42);
            DEBUG_PRINT(comm, "Etat: %d\n", etat);
            _delay_ms(1000);
 */        
        // //comm.transmissionChaine("Hello AVR!\n");
        // uint8_t etat = 3;
        // comm.transmissionFormatee("HSAHAHAA\n"); // PEUT TOTALEMENT REMPLACER: comm.transmissionChaine("Hello AVR!\n");
        // comm.transmissionFormatee("Val: %d et %d\n", etat, 42);

        // DEBUG_PRINT(comm, "Etat: %d\n", etat);      // affiche si make debug

        // _delay_ms(1000); // attend 1 seconde entre chaque envoi
/*         }
    }
    return 0;
 */



