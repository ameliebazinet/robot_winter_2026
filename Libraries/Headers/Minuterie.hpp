#include <avr/io.h>

enum class ModeMinuterie
{
    NORMAL, CTC, PWM
};

enum class ModeSortiePin // 0: A:PB3 B:PB4 / 1: A:PD5 B:PD4 / 2: A:PB7 B:PB6 
{
    NON, MONTANT, DESCENDANT, TOUT
};

class Minuterie
{   
public:
    Minuterie::Minuterie(uint8_t numeroMinuterie, ModeMinuterie mode, int8_t prescaler, ModeSortiePin modeSortiePin);
    void resetMinuterie();
    void partirMinuterie(float tempsMs);

    int8_t numeroMinuterie_;
    ModeMinuterie mode_;
    int8_t prescaler_; // 1, 8, 64, 256, 1024
    ModeSortiePin modeSortiePin_;

};

