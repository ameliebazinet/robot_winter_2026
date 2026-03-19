#define F_CPU 8000000UL
#include "memoire_24.h"
#include <util/delay.h>
#include <string.h>


char chaine[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
uint8_t chaineLu[46] = {};

Memoire24CXXX mem;

int main()
{
    DDRA |= (1 << PA0) | (1 << PA1);
    

    for (uint8_t i = 0; i < 46; i++)
    {
        mem.ecriture(i, chaine[i]);
        _delay_ms(5);
    }

    for (uint8_t i = 0; i < 46; i++)
    {
        mem.lecture(i, &chaineLu[i]);
    }

    while(true) 
    {
        if (strcmp(chaine, (char*)chaineLu) == 0) // vert
        {
            PORTA &= ~(1 << PA0);
		    PORTA |= (1 << PA1);
        }
        else // rouge
        {
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);
        }
    }
}