
#include "lecture.hpp"


int main()
{   

    // PontH::initialiserRegistre();
    // PontH::avancer(100);

   
    Lecture lecture; 
    lecture.initialiserLecture(); 
    lecture.lireMemoire();
    
    // //TEMPORAIRE - lire et afficher les 12 premiers octets
    // while(true)
    // {
    //     for (uint16_t i = 0; i < 42; i++) {
    //     uint8_t donnee;
    //     lecture.mem_.lecture(i, &donnee);
    //     lecture.com_.transmissionFormatee("addr %d = 0x%02X\r\n", i, donnee);
    // }

    // }

   
}