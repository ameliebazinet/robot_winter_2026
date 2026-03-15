#include <avr/io.h>
#include <avr/interrupt.h>
#include "Minuterie.hpp"

using namespace Minuterie;

// Variables statiques
uint16_t Minuterie0::prescaler_ = 0;
uint16_t Minuterie1::prescaler_ = 0;
uint16_t Minuterie2::prescaler_ = 0;

uint8_t Minuterie1::nbIterationsCompletesRestantes_ = 0;
int32_t Minuterie1::tempsRestantMs_ = 0;

// Minuterie0
void Minuterie0::configurer(WaveformGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
{
    switch (cs)
    {
        case OFF:
            prescaler_ = 0;
            break;
        case PRESCALER1:
            prescaler_ = 1;
            break;
        case PRESCALER8:
            prescaler_ = 8;
            break;
        case PRESCALER64:
            prescaler_ = 64;
            break;
        case PRESCALER256:
            prescaler_ = 256;
            break;
        case PRESCALER1024:
            prescaler_ = 1024;
            break;
    }

    TCCR0A = uint8_t(wgm) | uint8_t(comB) | uint8_t(comA);
    TCCR0B |= uint8_t(cs);
}

void Minuterie0::activerComparateurA(uint32_t tempsMs)
{
    OCR0A = (prescaler_ == 0) ? 0 : F_CPU / prescaler_ * tempsMs / 1000;
}
void Minuterie0::activerComparateurB(uint32_t tempsMs)
{
    OCR0B = (prescaler_ == 0) ? 0 : F_CPU / prescaler_ * tempsMs / 1000;
}

void Minuterie0::activerInteruptionComparateurA()
{
    TIMSK0 |= (1 << OCIE0A);
}
void Minuterie0::desactiverInteruptionComparateurA()
{
    TIMSK0 &= ~(1 << OCIE0A);
}

void Minuterie0::activerInteruptionComparateurB()
{
    TIMSK0 |= (1 << OCIE0B);
}
void Minuterie0::desactiverInteruptionComparateurB()
{
    TIMSK0 &= ~(1 << OCIE0B);
}

void Minuterie0::partirPWM(uint8_t ratioA, uint8_t ratioB)
{
    configurer(PWM, PRESCALER8, CLEAR_A, CLEAR_B);

    // Conversion du pourcentage en valeur de 0 à 255 (8 bits, car signal PWM sur registre à 8 bits)
    activerComparateurA(255 * ratioA / 100);
    activerComparateurB(255 * ratioB / 100);
}

// Minuterie1
void Minuterie1::configurer(WaveformGenerator1 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
{
    switch (cs)
    {
        case OFF:
            prescaler_ = 0;
            break;
        case PRESCALER1:
            prescaler_ = 1;
            break;
        case PRESCALER8:
            prescaler_ = 8;
            break;
        case PRESCALER64:
            prescaler_ = 64;
            break;
        case PRESCALER256:
            prescaler_ = 256;
            break;
        case PRESCALER1024:
            prescaler_ = 1024;
            break;
    }

    TCCR1A = uint8_t(wgm) | uint8_t(comB) | uint8_t(comA);
    TCCR1B |= uint8_t(cs);
    TCCR1C = 0;
}

void Minuterie1::activerComparateurA(uint32_t tempsMs)
{
    OCR1A = (prescaler_ == 0) ? 0 : F_CPU / prescaler_ * tempsMs / 1000;
}
void Minuterie1::activerComparateurB(uint32_t tempsMs)
{
    OCR1B = (prescaler_ == 0) ? 0 : F_CPU / prescaler_ * tempsMs / 1000;
}

void Minuterie1::activerInteruptionComparateurA()
{
    TIMSK1 |= (1 << OCIE1A);
}
void Minuterie1::desactiverInteruptionComparateurA()
{
    TIMSK1 &= ~(1 << OCIE1A);
}

void Minuterie1::activerInteruptionComparateurB()
{
    TIMSK1 |= (1 << OCIE1B);
}
void Minuterie1::desactiverInteruptionComparateurB()
{
    TIMSK1 &= ~(1 << OCIE1B);
}

void Minuterie1::partirMinuterie(uint32_t tempsMs, Comparateur c)
{
    // 16 bits (65536) / (8MHz / 1024) = 8388 ms
    const uint32_t tempsMaxMs = 8388;

    nbIterationsCompletesRestantes_ = tempsMs / tempsMaxMs;
    tempsRestantMs_ = tempsMs - (tempsMaxMs * nbIterationsCompletesRestantes_);
    
    cli();
    if (nbIterationsCompletesRestantes_ > 0) {
        activerComparateurA(tempsMaxMs);
        activerInteruptionComparateurA();
        configurer(NORMAL1, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        --nbIterationsCompletesRestantes_;
    }
    else {
        configurer(CTC1, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        activerComparateurA(tempsMs);
        activerInteruptionComparateurA();
        tempsRestantMs_ = 0;
    }
    sei();
}

void Minuterie1::miseAJourCompteur(volatile bool &estMinuterieExpiree)
{
    if (nbIterationsCompletesRestantes_ > 0) {
        --nbIterationsCompletesRestantes_;
    }
    else if (tempsRestantMs_ > 0) {
        configurer(CTC1, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        activerComparateurA(tempsRestantMs_);
        tempsRestantMs_ = 0;
    }
    else {
        estMinuterieExpiree = true;
    }
}

// Minuterie2
void Minuterie2::configurer(WaveformGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
{
    switch (cs)
    {
        case OFF:
            prescaler_ = 0;
            break;
        case PRESCALER1:
            prescaler_ = 1;
            break;
        case PRESCALER8:
            prescaler_ = 8;
            break;
        case PRESCALER64:
            prescaler_ = 64;
            break;
        case PRESCALER256:
            prescaler_ = 256;
            break;
        case PRESCALER1024:
            prescaler_ = 1024;
            break;
    }

    TCCR2A = uint8_t(wgm) | uint8_t(comB) | uint8_t(comA);
    TCCR2B |= uint8_t(cs);
}

void Minuterie2::activerComparateurA(uint32_t tempsMs)
{
    OCR2A = (prescaler_ == 0) ? 0 : F_CPU / prescaler_ * tempsMs / 1000;
}
void Minuterie2::activerComparateurB(uint32_t tempsMs)
{
    OCR2B = (prescaler_ == 0) ? 0 : F_CPU / prescaler_ * tempsMs / 1000;
}

void Minuterie2::activerInteruptionComparateurA()
{
    TIMSK2 |= (1 << OCIE2A);
}
void Minuterie2::desactiverInteruptionComparateurA()
{
    TIMSK2 &= ~(1 << OCIE2A);
}

void Minuterie2::activerInteruptionComparateurB()
{
    TIMSK2 |= (1 << OCIE2B);
}
void Minuterie2::desactiverInteruptionComparateurB()
{
    TIMSK2 &= ~(1 << OCIE2B);
}

void Minuterie2::partirPWM(uint8_t ratioA, uint8_t ratioB)
{
    cli();
    configurer(PWM, PRESCALER8, CLEAR_A, CLEAR_B);
    sei();

    // Conversion du pourcentage en valeur de 0 à 255 (8 bits, car signal PWM sur registre à 8 bits)
    OCR2A = 255 * ratioA / 100;
    OCR2B = 255 * ratioB / 100;
}