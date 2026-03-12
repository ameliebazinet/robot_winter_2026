#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "../lib/can.h"
#include "../lib/Del.hpp"


int main()
{

    const uint16_t LUMIERE_FAIBLE = 0xA0;
    const uint16_t LUMIERE_FORTE = 0xF0;  
    
    can convertisseur;
    
    DDRB |= (1 << PB0 | 1 << PB1);

    while (true) {
        uint16_t valeurLumiere = convertisseur.lecture(0) >> 2;

        if (valeurLumiere < LUMIERE_FAIBLE) {
            ajusterCouleur(Couleur::VERT);
            _delay_ms(DELAI_LED);
        }

        else if (valeurLumiere > LUMIERE_FORTE) {
            ajusterCouleur(Couleur::ROUGE);
            _delay_ms(DELAI_LED);
        }

        else {
            ajusterAmbre();
        }

}
    
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


}
