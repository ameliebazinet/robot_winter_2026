#include <avr/io.h>
#define F_CPU 8000000UL

// / 1: A:PD5 B:PD4 / 2: A:PB7 B:PB6

namespace Minuterie {

class Minuterie0
{
public:
    enum WaveFormGenerator0
    {
        NORMAL = 0,
        PWM = (1 << WGM00),
        CTC = (1 << WGM01)
    };

    enum CounterSelect0
    {
        OFF = 0,
        PRESCALER1 = (1 << CS00),
        PRESCALER8 = (1 << CS01),
        PRESCALER64 = (1 << CS01) | (1 << CS00),
        PRESCALER256 = (1 << CS02),
        PRESCALER1024 = (1 << CS02) | (1 << CS00)
    };

    // 0: A:PB3 B:PB4
    enum CompareOutputMode0A  
    {
        DECONNECTE_A = 0,
        TOGGLE_A = (1 << COM0A0),
        CLEAR_A = (1 << COM0A1),
        SET_A = (1 << COM0A1) | (1 << COM0A0)
    };

    enum CompareOutputMode0B 
    {
        DECONNECTE_B = 0,
        TOGGLE_B = (1 << COM0B0),
        CLEAR_B = (1 << COM0B1),
        SET_B = (1 << COM0B1) | (1 << COM0B0)
    };

    Minuterie0(WaveFormGenerator0 wgm, CounterSelect0 cs, CompareOutputMode0A comA, CompareOutputMode0B comB);

    // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
    // et le met directement dans OCR0A
    void activerComparateurA(uint8_t tempsMs);
    // Fait le calcul necessaire pour transformer le tempsMs en nb de cycle de minuterie
    // et le met directement dans OCR0B
    void activerComparateurB(uint8_t tempsMs);

    // Active l'interuption TIMER0_COMPA lorsque TCNT == OCR0A
    void activerInteruptionComparateurA();
    void desactiverInteruptionComparateurA();
    // Active l'interuption TIMER0_COMPB lorsque TCNT == OCR0B
    void activerInteruptionComparateurB();
    void desactiverInteruptionComparateurB();

    // Initialise tous les registres necessaire pour partir un signal PWM
    void PartirPWM(uint8_t ratio);

private:
    uint16_t prescaler_;
};

    class Minuterie1
    {
    };
    class Minuterie2
    {
    };

    // Combine le constructeur Minuterie0(),
    //         activerComparateur(A/B)(),
    //         activerInteruptionComparateur(A/B)() et
    //         commencer()
    //
    // Initialise tousles registres necessaire pour partir une minuterie
    // void PartirMinuterie();
}
