#include <avr/io.h>
class Del {
    public:
    Del(volatile uint8_t &port, uint8_t pin1, uint8_t pin2);

    // méthode pour ajuster la couleur de la del.
    enum class Color 
{
    GREEN,
    OFF,
    RED
};

    void AjusterCouleur(Color color ); 

  

}; 