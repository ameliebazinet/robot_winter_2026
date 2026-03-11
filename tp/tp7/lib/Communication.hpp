#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <stdarg.h>

class Communication {
public:
    void initialisationUART();
    void transmissionUART(uint8_t donnee);
    void transmissionChaine(const char* message);
    void transmissionFormatee(const char* format, ...);
};