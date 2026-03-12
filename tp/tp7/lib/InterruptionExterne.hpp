#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

class InterruptionExterne
{
public:
    void activerInterruptionsGlobales();
    void desactiverInterruptionsGlobales();
    void activerInterruption(uint8_t indiceInt);
    void desactiverInterruption(uint8_t indiceInt);
    bool estEnAttente(uint8_t indiceInt);
    void changerDetectionInterruption(uint8_t indiceInt, uint8_t detectionInterruption);
    bool estActiveeBroche(uint8_t indiceInt);
    void effacerFlag(uint8_t indiceInt);
    void initialisation(uint8_t indiceInt, uint8_t detectionInterruption);
};
