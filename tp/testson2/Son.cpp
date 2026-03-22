#include "Son.hpp"
#include <math.h>
#include <avr/interrupt.h>

void Son::init()
{
    // PB3 (OC0A)comme sortie
    DDRB |= (1 << PB3);

    // PB2 ground
    DDRB |= (1 << PB2);
    PORTB &= ~(1 << PB2);
}

void Son::jouerNote(uint8_t midi)
{
    uint8_t prescalerBits = 0;
    uint16_t ocr = midiToOCR(midi);
    uint16_t prescaler = choisirPrescaler(ocr, prescalerBits);

    cli();

    TCCR0A = (1 << COM0A0);
    TCCR0B = (1 << WGM01); 

    OCR0A = ocr / prescaler;

    TCCR0B |= prescalerBits;

    sei();
}

void Son::arreterNote()
{
    cli();
    TCCR0B = 0;
    PORTB &= ~(1 << PB3);
    sei();
}

uint16_t Son::midiToOCR(uint8_t midi)
{
    double freq = 440.0 * pow(2.0, (midi - 69) / 12.0);
    double ocr = F_CPU / (2.0 * 1.0 * freq) - 1;
    if (ocr < 1) ocr = 1;
    if (ocr > 255) ocr = 255;
    return static_cast<uint16_t>(ocr);
}

uint16_t Son::choisirPrescaler(uint16_t ocr, uint8_t &prescalerBits)
{
    if (ocr <= 255) { prescalerBits = (1 << CS00); return 1; }
    if ((ocr/8) <= 255) { prescalerBits = (1 << CS01); return 8; }
    if ((ocr/64) <= 255) { prescalerBits = (1 << CS01) | (1 << CS00); return 64; }
    if ((ocr/256) <= 255) { prescalerBits = (1 << CS02); return 256; }
    prescalerBits = (1 << CS02) | (1 << CS00);
    return 1024;
}