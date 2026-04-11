#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Son.hpp"

int main()
{
    Son::initialiserPiezo();

    // Jouer quelques notes : La2 (45), La3 (57), La4 (69), La5 (81)
    Son::jouer(45);
    _delay_ms(1000);

    Son::jouer(57);
    _delay_ms(1000);

    Son::jouer(69);
    _delay_ms(1000);

    Son::jouer(81);
    _delay_ms(1000);

    Son::arreter();

    while (true) {}
}