#include "lecture.hpp"

volatile bool tempsEcoule = false;
volatile bool boutonClique = false;

ISR(INT0_vect) {
    boutonClique = true;
}

ISR(TIMER1_COMPA_vect) {
    Minuterie::Minuterie1::miseAJourCompteur(tempsEcoule);
}

int main()
{   
   
    Lecture lecture; 
    lecture.selectionMode(boutonClique, tempsEcoule);
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
}