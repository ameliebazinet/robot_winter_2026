#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "../lib/Communication.hpp"
#include "../lib/debug.h"

int main()
{
    Communication comm;
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
        
        // //comm.transmissionChaine("Hello AVR!\n");
        // uint8_t etat = 3;
        // comm.transmissionFormatee("HSAHAHAA\n"); // PEUT TOTALEMENT REMPLACER: comm.transmissionChaine("Hello AVR!\n");
        // comm.transmissionFormatee("Val: %d et %d\n", etat, 42);

        // DEBUG_PRINT(comm, "Etat: %d\n", etat);      // affiche si make debug

        // _delay_ms(1000); // attend 1 seconde entre chaque envoi
        
        }
    }
    return 0;
}
