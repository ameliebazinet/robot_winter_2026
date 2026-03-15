#include <avr/io.h>
#include "Minuterie.hpp"
#include <avr/interrupt.h>

using namespace Minuterie;
uint16_t Minuterie0::prescaler_ = 0;

uint16_t Minuterie1::prescaler_ = 0;
uint8_t Minuterie1::nbIterationCompleteRestante_ = 0;
int32_t Minuterie1::tempsRestantMs_ = 0;

uint16_t Minuterie2::prescaler_ = 0;

void Minuterie0::configuration(WaveFormGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
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

    TCCR0B = 0;
    TCCR0A = 0;

    TCCR0A |= uint8_t(wgm);
    TCCR0B |= uint8_t(cs);
    TCCR0A |= uint8_t(comB);
    TCCR0A |= uint8_t(comA);
}

void Minuterie0::activerComparateurA(uint32_t tempsMs)
{
    if (prescaler_ == 0)
        OCR0A = 0;
    else
        OCR0A = F_CPU / prescaler_ * tempsMs / 1000;
}
void Minuterie0::activerComparateurB(uint32_t tempsMs)
{
    if (prescaler_ == 0)
        OCR0B = 0;
    else
        OCR0B = F_CPU / prescaler_ * tempsMs / 1000;
}

void Minuterie0::activerInteruptionComparateurA() // TIMSK0: OCIE0A pour ISR(vect.TIMER0_COMPA)
{
    TIMSK0 |= (1 << OCIE0A);
}
void Minuterie0::desactiverInteruptionComparateurA()
{
    TIMSK0 &= ~(1 << OCIE0A);
}

void Minuterie0::activerInteruptionComparateurB() // TIMSK0: OCIE0B pour ISR(vect.TIMER0_COMPB)
{
    TIMSK0 |= (1 << OCIE0B);
}
void Minuterie0::desactiverInteruptionComparateurB()
{
    TIMSK0 &= ~(1 << OCIE0B);
}

void Minuterie0::partirPWM(uint8_t ratioA, uint8_t ratioB)
{
    configuration(PWM, PRESCALER8, CLEAR_A, CLEAR_B);

    activerComparateurA(255 * ratioA / 100);
    activerComparateurB(255 * ratioB / 100);
}

void Minuterie1::configuration(WaveFormGenerator1 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
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

    TCCR1B = 0;
    TCCR1A = 0;
    TCCR1C = 0;

    TCCR1A |= uint8_t(wgm);
    TCCR1B |= uint8_t(cs);
    TCCR1A |= uint8_t(comB);
    TCCR1A |= uint8_t(comA);
}

void Minuterie1::activerComparateurA(uint32_t tempsMs)
{
    if (prescaler_ == 0)
        OCR1A = 0;
    else
    {
        OCR1A = F_CPU / prescaler_ * tempsMs / 1000;
    }
}
void Minuterie1::activerComparateurB(uint32_t tempsMs)
{
    if (prescaler_ == 0)
        OCR1B = 0;
    else
        OCR1B = F_CPU / prescaler_ * tempsMs / 1000;
}

void Minuterie1::activerInteruptionComparateurA() // TIMSK1: OCIE1A pour ISR(TIMER1_COMPA_vect)
{
    TIMSK1 |= (1 << OCIE1A);
}
void Minuterie1::desactiverInteruptionComparateurA()
{
    TIMSK1 &= ~(1 << OCIE1A);
}

void Minuterie1::activerInteruptionComparateurB() // TIMSK1: OCIE1B pour ISR(TIMER1_COMPB_vect)
{
    TIMSK1 |= (1 << OCIE1B);
}
void Minuterie1::desactiverInteruptionComparateurB()
{
    TIMSK1 &= ~(1 << OCIE1B);
}

void Minuterie1::partirMinuterie(uint32_t tempsMs, Comparateur c)
{
    const uint32_t tempsMaxMs = 8388;

    nbIterationCompleteRestante_ = tempsMs / tempsMaxMs;
    tempsRestantMs_ = tempsMs - (tempsMaxMs * nbIterationCompleteRestante_);

    if (nbIterationCompleteRestante_ > 0)
    {
        cli();
        activerComparateurA(tempsMaxMs);
        activerInteruptionComparateurA();
        configuration(NORMAL1, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        sei();
        --nbIterationCompleteRestante_;
    }
    else
    {
        cli();
        configuration(CTC1, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        activerComparateurA(tempsMs);
        activerInteruptionComparateurA();
        sei();
        tempsRestantMs_ = 0;
    }
}

void Minuterie1::miseAJourCompteur(volatile bool& estMinuterieExpire)
{
    if (nbIterationCompleteRestante_ > 0)
    {
        --nbIterationCompleteRestante_;
    }
    else if (tempsRestantMs_ > 0)
    {
        configuration(CTC1, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        activerComparateurA(tempsRestantMs_);
        tempsRestantMs_ = 0;
    }
    else
    {
        estMinuterieExpire = true;
    }
}

void Minuterie2::configuration(WaveFormGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
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

    TCCR2B = 0;
    TCCR2A = 0;

    TCCR2A |= uint8_t(wgm);
    TCCR2B |= uint8_t(cs);
    TCCR2A |= uint8_t(comB);
    TCCR2A |= uint8_t(comA);
}

void Minuterie2::activerComparateurA(uint32_t tempsMs)
{
    if (prescaler_ == 0)
        OCR2A = 0;
    else
        OCR2A = F_CPU / prescaler_ * tempsMs / 1000;
}
void Minuterie2::activerComparateurB(uint32_t tempsMs)
{
    if (prescaler_ == 0)
        OCR2B = 0;
    else
        OCR2B = F_CPU / prescaler_ * tempsMs / 1000;
}

void Minuterie2::activerInteruptionComparateurA() // TIMSK2: OCIE2A pour ISR(vect.TIMER2_COMPA)
{
    TIMSK2 |= (1 << OCIE2A);
}
void Minuterie2::desactiverInteruptionComparateurA()
{
    TIMSK2 &= ~(1 << OCIE2A);
}

void Minuterie2::activerInteruptionComparateurB() // TIMSK2: OCIE2B pour ISR(vect.TIMER2_COMPB)
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
    configuration(PWM, PRESCALER8, CLEAR_A, CLEAR_B);
    sei();

    OCR2A = 255 * ratioA / 100;
    OCR2B = 255 * ratioB / 100;
}