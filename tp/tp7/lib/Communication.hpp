#include <stdint.h>

class Communication {
public:

    void initialisationUART(); 
    void transmissionUART(uint8_t donnee); 
    void transmissionChaine(const char* message);

};