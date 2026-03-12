#include <avr/io.h>
#include "Minuterie.hpp"

using namespace Minuterie;

void Minuterie0::configuration(WaveFormGenerator wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
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

void Minuterie0::PartirPWM(uint8_t ratioDroite, uint8_t ratioGauche)
{
    configuration(PWM, PRESCALER8, CLEAR_A, CLEAR_B);

    activerComparateurA(255 * ratioDroite / 100);
    activerComparateurB(255 * ratioGauche / 100);
}

void Minuterie1::configuration(WaveFormGenerator wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
{
    uint16_t prescaler;
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

    TCCR1B = 0;
    TCCR1A = 0;

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
        OCR1A = F_CPU / prescaler_ * tempsMs / 1000;
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
    const uint16_t tempsMaxMs = 8388;

    nbIterationRestante_ = tempsMs / tempsMaxMs;
    tempsRestantMs_ = tempsMs - tempsMaxMs * nbIterationRestante_;

    configuration(NORMAL, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
    activerComparateurA(tempsMaxMs);
    activerInteruptionComparateurA();
}

void Minuterie1::miseAJourCompteur()
{
    if (nbIterationRestante_ != 0)
    {
        --nbIterationRestante_;
    }
    else if (nbIterationRestante_ == 0)
    {
        --nbIterationRestante_;
        configuration(CTC, PRESCALER1024, DECONNECTE_A, DECONNECTE_B);
        activerComparateurA(tempsRestantMs_);
    }
    else
    {
        estMinuterieExpire_ = true;
    }
}

void Minuterie2::configuration(WaveFormGenerator wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB)
{
    uint16_t prescaler;
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

    TCCR2B = 0;
    TCCR2A = 0;

    TCCR2A |= uint8_t(wgm);
    TCCR2B |= uint8_t(cs);
    TCCR2A |= uint8_t(comB);
    TCCR2A |= uint8_t(comA);
}

void Minuterie0::activerComparateurA(uint32_t tempsMs)
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

void Minuterie2::PartirPWM(uint8_t ratioDroite, uint8_t ratioGauche)
{
    configuration(PWM, PRESCALER8, CLEAR_A, CLEAR_B);

    activerComparateurA(255 * ratioDroite / 100);
    activerComparateurB(255 * ratioGauche / 100);
}