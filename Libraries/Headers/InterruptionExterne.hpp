#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class InterruptionExterne
{
public:
    void initialisation(uint8_t indiceInt, uint8_t interruptSenseControl);
    void changerSenseControl(uint8_t indiceInt, uint8_t interruptSenseControl);
    bool interruptionEnAttente(uint8_t indiceInt);
    void activerInterruption(uint8_t indiceInt);
    void reprendreInterruptionExterne();
    void effacerFlag(uint8_t indiceInt);
    bool lireEtatBroche(uint8_t indiceInt);
    void desactiverInterruptionsGlobales();
    void activerInterruptionsGlobales();
};
