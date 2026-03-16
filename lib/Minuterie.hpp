// Fichier : Minuterie.hpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Déclaration des méthodes pour la configuration et l'utilisation des minuteries 0, 1 et 2.

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>

namespace Minuterie
{
    // Enums
    enum WaveformGenerator02
    {
        NORMAL = (0 << WGM01) | (0 << WGM00),
        PWM = (0 << WGM01) | (1 << WGM00),
        CTC = (1 << WGM01) | (0 << WGM00)
    };

    enum WaveformGenerator1
    {
        NORMAL1 = (0 << WGM13) | (0 << WGM12) | (0 << WGM11) | (0 << WGM10),
        PWM1 = (0 << WGM13) | (0 << WGM12) | (0 << WGM11) | (1 << WGM10),
        CTC1 = (0 << WGM13) | (1 << WGM12) | (0 << WGM11) | (0 << WGM10)
    };

    enum CounterSelect
    {
        OFF = (0 << CS02) | (0 << CS01) | (0 << CS00),
        PRESCALER1 = (0 << CS02) | (0 << CS01) | (1 << CS00),
        PRESCALER8 = (0 << CS02) | (1 << CS01) | (0 << CS00),
        PRESCALER64 = (0 << CS02) | (1 << CS01) | (1 << CS00),
        PRESCALER256 = (1 << CS02) | (0 << CS01) | (0 << CS00),
        PRESCALER1024 = (1 << CS02) | (0 << CS01) | (1 << CS00)
    };

    // 0: PB3 / 1: PD5 / 2: PD7
    enum CompareOutputModeA
    {
        DECONNECTE_A = (0 << COM0A1) | (0 << COM0A0),
        TOGGLE_A = (0 << COM0A1) | (1 << COM0A0),
        CLEAR_A = (1 << COM0A1) | (0 << COM0A0),
        SET_A = (1 << COM0A1) | (1 << COM0A0)
    };
    
    // 0: PB4 / 1: PD4 / 2: PD6
    enum CompareOutputModeB
    {
        DECONNECTE_B = (0 << COM0B1) | (0 << COM0B0),
        TOGGLE_B = (0 << COM0B1) | (1 << COM0B0),
        CLEAR_B = (1 << COM0B1) | (0 << COM0B0),
        SET_B = (1 << COM0B1) | (1 << COM0B0)
    };

    enum Comparateur
    {
        A,
        B
    };

    // Minuterie 0 (sur 8 bits)
    class Minuterie0
    {
    public:
        // Configure les registres de la minuterie pour sont utilisation.
        static void configurer(WaveformGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met dans OCR0A
        static void activerComparateurA(uint32_t tempsMs);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met dans OCR0B
        static void activerComparateurB(uint32_t tempsMs);

        // Active l'interuption TIMER0_COMPA_vect lorsque le comparateur (OCR0A) s'active.
        static void activerInteruptionComparateurA();

        // Désactive l'interuption TIMER0_COMPA_vect.
        static void desactiverInteruptionComparateurA();

        // Active l'interuption TIMER0_COMPB_vect lorsque le comparateur (OCR0B) s'active.
        static void activerInteruptionComparateurB();

        // Désactive l'interuption TIMER0_COMPB_vect.
        static void desactiverInteruptionComparateurB();

        // Initialise tous les registres necessaire pour partir un signal PWM.
        // Les ratios doivent etre compris entre 0 et 100 inclusivement.
        // OC0A => PB3; OC0B => PB4
        static void partirPWM(uint8_t ratioA, uint8_t ratioB);

    private:
        static uint16_t prescaler_;
    };

    class Minuterie1
    {
    public:
        // Configure les registres de la minuterie pour sont utilisation.
        static void configurer(WaveformGenerator1 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met dans OCR1A.
        static void activerComparateurA(uint32_t tempsMs);
        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met dans OCR1B.
        static void activerComparateurB(uint32_t tempsMs);

        // Active l'interuption TIMER1_COMPA_vect lorsque le comparateur (OCR1A) s'active.
        static void activerInteruptionComparateurA();
        static void desactiverInteruptionComparateurA();
        // Active l'interuption TIMER1_COMPB_vect lorsque le comparateur (OCR1B) s'active.
        static void activerInteruptionComparateurB();
        static void desactiverInteruptionComparateurB();

        // Initialise tous les registres necessaire pour partir une minuterie.
        // Dans le fichier main, doit configurer ISR(TIMER1_COMPA_vect)
        // pour appelé timer.miseAJourCompteur(estMinuterieExpiree).
        static void partirMinuterie(uint32_t tempsMs, Comparateur c);
        static void miseAJourCompteur(volatile bool &estMinuterieExpiree);

    private:
        static uint16_t prescaler_;
        static uint8_t nbIterationsCompletesRestantes_;
        static int32_t tempsRestantMs_;
    };

    class Minuterie2
    {
    public:
        // Configure les registres de la minuterie pour sont utilisation.
        static void configurer(WaveformGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met dans OCR2A.
        static void activerComparateurA(uint32_t tempsMs);
        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met dans OCR2B.
        static void activerComparateurB(uint32_t tempsMs);

        // Active l'interuption TIMER2_COMPA_vect lorsque le comparateur (OCR2A) s'active.
        static void activerInteruptionComparateurA();
        static void desactiverInteruptionComparateurA();
        // Active l'interuption TIMER2_COMPB_vect lorsque le comparateur (OCR2B) s'active.
        static void activerInteruptionComparateurB();
        static void desactiverInteruptionComparateurB();

        // Initialise tous les registres necessaire pour partir un signal PWM.
        // Les ratios doivent etre compris entre 0 et 100 inclusivement.
        // OC2A => PD7 / OC2B => PD6
        static void partirPWM(uint8_t ratioA, uint8_t ratioB);

    private:
        static uint16_t prescaler_;
    };
}
