#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Son.hpp"

// 107 BPM → 1 noire = 561 ms → 1 croche = 280 ms
static const uint16_t CROCHE_MS = 280;

void initialiserPiezo()
{
    DDRD |= (1 << PD5) | (1 << PD4);
    PORTD &= ~((1 << PD5) | (1 << PD4));
}

void jouerNote(uint8_t note)
{
    Son::jouer(note);
    _delay_ms(252);
    Son::arreter();
    _delay_ms(28);
}

int main()
{
    initialiserPiezo();

    while (true) {
        for (uint8_t i = 0; i < 6; i++) jouerNote(76);
        for (uint8_t i = 0; i < 2; i++) jouerNote(69);
        for (uint8_t i = 0; i < 6; i++) jouerNote(77);
        for (uint8_t i = 0; i < 2; i++) jouerNote(74);
    }

    return 0;
}