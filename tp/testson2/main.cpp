#include "Son.hpp"
#include <util/delay.h>

int main()
{
    Son::init();

    while (1)
    {
        Son::jouerNote(69);
        _delay_ms(500);
        Son::arreterNote();
        _delay_ms(200);

        Son::jouerNote(72);
        _delay_ms(500);
        Son::arreterNote();
        _delay_ms(200);
    }
}