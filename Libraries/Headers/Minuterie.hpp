#include <avr/io.h>

//void partirMinuterie(float tempsMs);
//void ajustementPwm();

namespace Minuterie 
{
    enum WaveFormGenerator
    {
        NORMAL = 0, 
        CTC    = (1 << WGM01), 
        PWM    = (1 << WGM00)
    };

    enum CounterSelect
    {
        PRESCALER1    = 0, 
        PRESCALER8    = (1 << CS00), 
        PRESCALER64   = (1 << CS01), 
        PRESCALER256  = (1 << CS01) | (1 << CS00), 
        PRESCALER1024 = (1 << CS02)
    };
    
    enum CompareOutputMode // 0: A:PB3 B:PB4 / 1: A:PD5 B:PD4 / 2: A:PB7 B:PB6 
    {
        DECONNECTE = 0, 
        TOGGLE     = (1 << COM00), 
        CLEAR      = (1 << COM01), 
        SET        = (1 << COM01) | (1 << COM01)
    };
    
    class Minuterie0
    {   
    public:
        void reinitialiserRegistre();
        
        Minuterie0(WaveFormGenerator wgm, CounterSelect cs, CompareOutputMode com);
        void commencer();
        void arreter();

        void activerComparateurA(int tempsMs);
        void activerComparateurB(int tempsMs);

        void activerInteruptionComparateurA();
        void desactiverInteruptionComparateurA();
        void activerInteruptionComparateurB();
        void desactiverInteruptionComparateurB();

        
    
    private:
    };

    class Minuterie1 {};
    class Minuterie2 {};
}



