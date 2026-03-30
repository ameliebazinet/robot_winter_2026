#include "CapteurInfra.hpp"
#include "Communication.hpp"


int main()
{
    CapteurInfra ci;
    Communication com;
    com.initialisationUART();

    while (true)
    {
        ci.lireVoltage();
        com.transmissionFormatee("voltage lu: %d \r\n", ci.voltage);
    }
}