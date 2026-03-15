#include <avr/io.h>
#define F_CPU 8000000UL

namespace Minuterie
{
    enum WaveFormGenerator02
    {
        NORMAL = (0 << WGM01) | (0 << WGM00),
        PWM = (0 << WGM01) | (1 << WGM00),
        CTC = (1 << WGM01) | (0 << WGM00)
    };
    enum WaveFormGenerator1
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

    class Minuterie0
    {
    public:
        static void configuration(WaveFormGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR0A
        static void activerComparateurA(uint32_t tempsMs);
        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR0B
        static void activerComparateurB(uint32_t tempsMs);

        // Active l'interuption TIMER0_COMPA lorsque TCNT0 == OCR0A
        static void activerInteruptionComparateurA();
        static void desactiverInteruptionComparateurA();
        // Active l'interuption TIMER0_COMPB lorsque TCNT0 == OCR0B
        static void activerInteruptionComparateurB();
        static void desactiverInteruptionComparateurB();

        // Initialise tous les registres necessaire pour partir un signal PWM
        static void partirPWM(uint8_t ratioA, uint8_t ratioB);

    private:
        static uint16_t prescaler_;
    };

    class Minuterie1
    {
    public:
        static void configuration(WaveFormGenerator1 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR1A
        static void activerComparateurA(uint32_t tempsMs);
        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR1B
        static void activerComparateurB(uint32_t tempsMs);

        // Active l'interuption TIMER1_COMPA lorsque TCNT1 == OCR1A
        static void activerInteruptionComparateurA();
        static void desactiverInteruptionComparateurA();
        // Active l'interuption TIMER1_COMPB lorsque TCNT1 == OCR1B
        static void activerInteruptionComparateurB();
        static void desactiverInteruptionComparateurB();

        // Initialise tous les registres necessaire pour partir une minuterie
        // Dans le fichier main, doit configurer I R(TIMER1_COMPA_vect) pour appelé timer.miseAJourCompteur() et
        // Dans le main, la logique doit etre mis tel que: while (!timer.expired){ //logique }
        static void partirMinuterie(uint32_t tempsMs, Comparateur c);

        static void miseAJourCompteur(volatile bool& estMinuterieExpire);

    private:
        static uint16_t prescaler_;
        static uint8_t nbIterationCompleteRestante_;
        static int32_t tempsRestantMs_;
    };

    class Minuterie2
    {
    public:
        static void configuration(WaveFormGenerator02 wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comB);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR2A
        static void activerComparateurA(uint32_t tempsMs);
        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR2B
        static void activerComparateurB(uint32_t tempsMs);

        // Active l'interuption TIMER2_COMPA lorsque TCNT2 == OCR2A
        static void activerInteruptionComparateurA();
        static void desactiverInteruptionComparateurA();
        // Active l'interuption TIMER2_COMPB lorsque TCNT2 == OCR2B
        static void activerInteruptionComparateurB();
        static void desactiverInteruptionComparateurB();

        // Initialise tous les registres necessaire pour partir un signal PWM
        static void partirPWM(uint8_t ratioA, uint8_t ratioB);

    private:
        static uint16_t prescaler_;
    };
}
