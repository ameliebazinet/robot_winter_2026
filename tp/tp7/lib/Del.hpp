#include <avr/io.h>
class Del {
    public:
    
    // L'objet sera uniquement valide si nous passons 
    // des valeurs à pin1 et pin2 entre 0 et 7. 
    Del(volatile uint8_t &port, uint8_t pin1, uint8_t pin2_);
                                                        
    enum class Couleur 
    {
        ETEINT,
        VERT,
        ROUGE
    };
    
    // Allume la DEL selon la couleur spécifié dans l'énumération Couleur. 
    void allumerCouleur(Couleur couleur); 
    // Simule la couleur ambre sur la DEL.  
    void allumerCouleurAmbre();

    private : 
    volatile uint8_t &port_;
    uint8_t pin1_;
    uint8_t pin2_;


  

}; 