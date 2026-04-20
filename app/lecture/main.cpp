// Fichier : main.cpp
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Programme principal du mode lecture.
// Initialise les interruptions et gère la sélection du mode d'opération du robot.
// Ce main et ce Makefile ne sont pas utilisés durant l'execution du programme final
// et servent à tester la lecture de l'EEPROM.

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
    sei();
    lecture.selectionnerMode(boutonClique, tempsEcoule);
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