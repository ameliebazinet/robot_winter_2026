// Fichier : Del.hpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (...), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Cette classe déclare les méthodes pour la manipulation d'une DEL à deux broches.

#include <avr/io.h>
#include <stdint.h>

class Del 
{
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
    
    // Allume la DEL selon la couleur spécifiée de l'énumération Couleur 
    void allumerCouleur(Couleur couleur); 

    // Simule la couleur ambre sur la DEL.  
    void allumerCouleurAmbre();

private : 
    volatile uint8_t &port_;
    uint8_t pin1_;
    uint8_t pin2_;
}; 