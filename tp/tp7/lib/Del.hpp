#include <avr/io.h>
class Del {
    public:
    Del(volatile uint8_t &port_, uint8_t pin1_, uint8_t pin2_);
    // attention, l'objet sera uniquement valide si nous passons 
    // des valeurs à pin1 et pin2 entre 0 et 7. 
                                                        
    enum class Couleur 
    {
        ETEINT,
        VERT,
        ROUGE
    };


    
    void ajusterCouleur(Couleur couleur); 
    void ajusterAmbre();


    private : 

    volatile uint8_t &port_;
    uint8_t pin1_;
    uint8_t pin2_;


  

}; 