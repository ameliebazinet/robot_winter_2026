#include <avr/io.h>
class Del {
    public:
    Del(volatile uint8_t &port, uint8_t pin1, uint8_t pin2);  // attention, l'objet sera uniquement valide si nous passons des valeur à Pin1 et Pin2 entre 0 et 7. 
                                                        

    // méthode pour ajuster la couleur de la del.
    enum class Couleur 
    {
        VERT,
        ETEINT,
        ROUGE
    };


    
    void ajusterCouleur(Couleur couleur); 


    private : 

    volatile uint8_t &port;
    uint8_t pin1;
    uint8_t pin2;


  

}; 