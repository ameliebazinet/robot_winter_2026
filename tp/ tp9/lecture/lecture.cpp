#define F_CPU 8000000UL
#include <util/delay.h>
#include "Communication.hpp"
#include "memoire_24.h"
#include "Del.hpp"
#include "PontH.hpp"

// INCLUDE SON

constexpr uint8_t ADRESSE_TAILLE = 2;

enum Instruction {
    DEBUT = 0b00000001,
    ATTENDRE = 0b00000010,
    ALLUMER_LED = 0b01000100,
    ETEINDRE_LED = 0b01000101,
    JOUER_SON = 0b01001000,
    ARRETER_SON = 0b00001001,
    ARRETER_MOTEURS = 0b01100000,
    ARRETER_MOTEURS = 0b01100001,
    AVANCER = 0b01100010, 
    RECULER = 0b01100011, 
    TOURNER_DROITE = 0b01100100,
    TOURNER_GAUCHE = 0b01100101, 
    DEBUT_BOUCLE = 0b11000000, 
    FIN_BOUCLE = 0b11000001, 
    FIN = 0b11111111
};

int main()
{
    Communication com;
    Memoire24CXXX mem;
    com.initialisationUART();

    uint8_t instruction = 0b00;
    uint8_t operande = 0b00;
    uint16_t adresse = 0x0000;
    uint8_t donnee = 0;

    uint16_t taille = mem.lecture(adresse, (uint8_t*)&donnee);
    adresse++;
    taille << 8;
    taille += mem.lecture(adresse, (uint8_t*)&donnee);


    for (uint8_t i = 0; i < taille; i++ ) {
        instruction = mem.lecture(adresse++, &donnee);
        operande = mem.lecture(adresse++, &donnee);

        // Brancher le DEL sur PA0 et PA1
        Del del(PORTA, PA0, PA1);

        // Brancher moteur sur PD4 (direction gauche), PD5 (direction droite),
        // PD6 (activer gauche) et PD7 (activer droite)
        PontH::initialiserRegistre();
        PontH moteur;

        uint16_t adresseBoucle = 0;
        uint8_t compteurBoucle = 0;

        if (instruction == DEBUT) {

            switch (instruction) {
                case ATTENDRE:
                    _delay_ms(25 * operande);
                    break;
                
                case ALLUMER_LED:
                    if (operande == 1) {
                        del.allumerCouleur(Del::Couleur::VERT);
                    }
                    else if (operande == 2) {
                        del.allumerCouleur(Del::Couleur::ROUGE);
                    }
                    else {
                        del.allumerCouleur(Del::Couleur::ETEINT);
                    }

                    break;

                case ETEINDRE_LED:
                    del.allumerCouleur(Del::Couleur::ETEINT);
                    break;

                case JOUER_SON:
                    break;

                case ARRETER_SON:
                    break;

                case ARRETER_MOTEURS:
                    moteur.arreter();
                    break;
                    
                case AVANCER:
                    moteur.avancer(operande / 255 * 100);
                    break;

                case RECULER:
                    moteur.reculer(operande / 255 * 100);
                    break;

                case TOURNER_DROITE:
                    break;

                case TOURNER_GAUCHE:
                    break;

                case DEBUT_BOUCLE:
                    adresseBoucle = adresse;
                    compteurBoucle = operande + 1;
                    break;
                
                case FIN_BOUCLE:
                    if (compteurBoucle != 0) {
                        compteurBoucle--;
                        adresse = adresseBoucle;
                    }
                    break;

                case FIN:
                    adresse = adresse + taille;
                    break;
            }
        }
        
        else {
            continue;
        }

    }
    
    // SWITCH CASE : CHAQUE INSTRUCTION CODER QUOI FAIRE

    return 1;
}