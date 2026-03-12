#include <avr/io.h>
#include "Minuterie.hpp"

using namespace Minuterie;

enum Chemin
{
    A,
    B
};

Minuterie0::Minuterie0(WaveFormGenerator0 wgm, CounterSelect0 cs, CompareOutputMode0A comA, CompareOutputMode0B comB)
{
    switch (cs)
    {
    case OFF:
        prescaler = 0;
        break;
    case PRESCALER1:
        prescaler = 1;
        break;
    case PRESCALER8:
        prescaler = 8;
        break;
    case PRESCALER64:
        prescaler = 64;
        break;
    case PRESCALER256:
        prescaler = 256;
        break;
    case PRESCALER1024:
        prescaler = 1024;
        break;
    }

    TCCR0B = 0;
    TCCR0A = 0;

    TCCR0A |= uint8_t(wgm);
    TCCR0B |= uint8_t(cs);
    TCCR0A |= uint8_t(comB);
    TCCR0A |= uint8_t(comA);
    //     TCCR0B |= ((wgm & 0b100) << DECALAGE_WGM02) | (cs & 0b100) | (cs & 0b010) | (cs & 0b001);
    //     TCCR0A |= (comA & 0b10) | (comA & 0b01) | (comB & 0b10) | (comB & 0b01) | (wgm & 0b010) | (wgm & 0b001);
}

void Minuterie0::activerComparateurA(uint8_t tempsMs)
{
    if (prescaler == 0)
        OCR0A = 0;
    else
        OCR0A = F_CPU / prescaler * tempsMs / 1000;
}
void Minuterie0::activerComparateurB(uint8_t tempsMs)
{
    if (prescaler == 0)
        OCR0B = 0;
    else
        OCR0B = F_CPU / prescaler * tempsMs / 1000;
}

void Minuterie0::activerInteruptionComparateurA() // TIMSK0: OCIE0A pour ISR(vect.TIMER0_COMPA)
{
    TIMSK0 = (1 << OCIE0A);
}
void Minuterie0::desactiverInteruptionComparateurA()
{
    TIMSK0 = (0 << OCIE0A);
}

void Minuterie0::activerInteruptionComparateurB() // TIMSK0: OCIE0B pour ISR(vect.TIMER0_COMPB)
{
    TIMSK0 = (1 << OCIE0B);
}
void Minuterie0::desactiverInteruptionComparateurB()
{
    TIMSK0 = (0 << OCIE0B);
} 

void Minuterie0::PartirPWM(uint8_t ratio)
{
    Minuterie0 m0 = Minuterie0(PWM, PRESCALER8, CLEAR_A, CLEAR_B);

    activerComparateurA(255 * ratio / 100);
    activerComparateurB(255 * ratio / 100);
}

// static void PartirMinuterie(int tempsMs, Type type)
//  {
//      switch (type)
//      {  
//      case A:
//          Minuterie0 m0 = Minuterie0(CTC, PRESCALER1024, OFF, OFF);
//          activerComparateurA(tempsMs);
//          activerInteruptionComparateurA();
//          break;

//     case B:
//         Minuterie0 m0 = Minuterie0(CTC, PRESCALER1024, OFF, OFF);
//         activerComparateurB(tempsMs);
//         activerInteruptionComparateurB();
//         break;
//     }
// }