#include <avr/io.h>
#include <stdexcept>
#include "Minuterie.hpp"

Minuterie(uint8_t numeroMinuterie, WGM mode, int8_t prescaler, ModeSortiePin modeSortiePin)
{
    // Verif param
    if (false){
        throw exception_type("Paramètres de minuterie mals initialisés");
    }

    numeroMinuterie_ = numeroMinuterie;
    mode_ = mode;
    prescaler_ = prescaler
    modeSortiePin_ = modeSortiePin;
}

void Minuterie::resetMinuterie()
{
    switch (numeroMinuterie_)
    {
    case 0:
        TCNT0 = 0;
        break;

    case 1:
        TCNT1 = 0;
        break;

    case 2:
        TCNT2 = 0;
        break;
    }
}

void Minuterie::partirMinuterie(float tempsMs)
{
}
