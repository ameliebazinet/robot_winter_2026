#pragma once

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 8000000UL

class Son
{
public:
    // Initialise la pin et le timer
    static void init();

    // Joue une note MIDI (ex: 69 = A4)
    static void jouerNote(uint8_t midi);

    // Arrête le son
    static void arreterNote();

private:
    // Convertit MIDI en valeur OCR0A pour CTC toggle
    static uint16_t midiToOCR(uint8_t midi);

    // Choisit le prescaler pour que OCR0A soit < 255
    static uint16_t choisirPrescaler(uint16_t ocr, uint8_t &prescalerBits);
};
