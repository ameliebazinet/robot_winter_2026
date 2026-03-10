#include "memoire_24.h"
class Communication {
    public:
    Communication(Memoire24CXXX memoire, uint16_t adresse, uint8_t donnee);

    void initialisationUART(); 
    void transmissionUART(uint8_t donnee); 

    private:
    Memoire24CXXX memoire_;
    uint16_t adresse_;
    uint8_t donnee_;

};