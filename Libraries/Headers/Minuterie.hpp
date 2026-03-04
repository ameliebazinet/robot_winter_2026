#include <avr/io.h>
#define F_CPU 8000000UL

// void partirMinuterie(float tempsMs);
// void ajustementPwm();

namespace Minuterie
{

    enum WaveFormGenerator
    {
        NORMAL = 0,
        CTC = (1 << WGM01),
        PWM = (1 << WGM00)
    };

    enum CounterSelect
    {
        OFF = 0,
        PRESCALER1 = (1 << CS00),
        PRESCALER8 = (1 << CS01),
        PRESCALER64 = (1 << CS01) | (1 << CS00),
        PRESCALER256 = (1 << CS02),
        PRESCALER1024 = (1 << CS02) | (1 << CS00)
    };

    enum CompareOutputModeA // 0: A:PB3 B:PB4 / 1: A:PD5 B:PD4 / 2: A:PB7 B:PB6
    {
        DECONNECTE = 0,
        TOGGLE = (1 << COM0A0),
        CLEAR = (1 << COM0A1),
        SET = (1 << COM0A1) | (1 << COM0A0)
    };

    enum CompareOutputModeB // 0: A:PB3 B:PB4 / 1: A:PD5 B:PD4 / 2: A:PB7 B:PB6
    {
        DECONNECTE = 0,
        TOGGLE = (1 << COM0B0),
        CLEAR = (1 << COM0B1),
        SET = (1 << COM0B1) | (1 << COM0B0)
    };

    class Minuterie0
    {
    public:
        Minuterie0(WaveFormGenerator wgm, CounterSelect cs, CompareOutputModeA comA, CompareOutputModeB comb);

        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR0A
        void activerComparateurA(int tempsMs);
        // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
        // et le met directement dans OCR0B
        void activerComparateurB(int tempsMs);

        // Active l'interuption TIMER0_COMPA lorsque TCNT == OCR0A
        void activerInteruptionComparateurA();
        void desactiverInteruptionComparateurA();
        // Active l'interuption TIMER0_COMPB lorsque TCNT == OCR0B
        void activerInteruptionComparateurB();
        void desactiverInteruptionComparateurB();

        // Combine le constructeur Minuterie0(),
        //         activerComparateur(A/B)(),
        //         activerInteruptionComparateur(A/B)() et
        //         commencer()
        //
        // Initialise tousles registres necessaire pour partir une minuterie
        void PartirMinuterie();

        // Initialise tous les registres necessaire pour partir un signal PWM
        void PartirPWM(uint8_t ratio);

    private:
        CounterSelect prescaler;
    };

    class Minuterie1
    {
    };
    class Minuterie2
    {
    };
}
