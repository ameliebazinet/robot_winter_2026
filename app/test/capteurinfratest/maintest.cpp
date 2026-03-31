#include "CapteurInfra.hpp"
#include "Communication.hpp"
#include "Del.hpp"

int main()
{
    CapteurInfra ci;
    Communication com;
    com.initialisationUART();
    Del del(PORTA, PA2, PA3);

    while (true)
    {
        // com.transmissionFormatee("distance lue: %d \r\n", ci.distance);

        
        ci.lireDistance();
        if(ci.estObjetDetecte()){
            del.allumerCouleur(Del::Couleur::ROUGE);

        }
        else{
            del.allumerCouleur(Del::Couleur::VERT);
        }
    }
}

// 17cm
// 30 cm
// 23-26 cm
