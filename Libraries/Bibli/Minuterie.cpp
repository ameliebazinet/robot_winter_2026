#include <avr/io.h>
#include "Minuterie.hpp"

using namespace Minuterie;

void Minuterie0::reinitialiserRegistre()
{
    TCCR0B = 0;
    TCCR0A = 0;

    //
}

Minuterie0::Minuterie0(WaveFormGenerator wgm, CounterSelect cs, CompareOutputMode com)
{
    const uint8_t DECALAGE_WGM02 = 1;
    //TCCR0B |= ((1 << WGM02) << DECALAGE_WGM02)
    // TCCR0A |= 
}

void Minuterie0::commencer()
{
}
void Minuterie0::arreter()
{
}

void Minuterie0::activerComparateurA(int tempsMs)
{
}
void Minuterie0::activerComparateurB(int tempsMs)
{
}

void Minuterie0::activerInteruptionComparateurA()
{
}
void Minuterie0::desactiverInteruptionComparateurA()
{
}
void Minuterie0::activerInteruptionComparateurB()
{
}
void Minuterie0::desactiverInteruptionComparateurB()
{
}