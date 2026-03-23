#define DEBUG 
#include "lecture.hpp"
#include "debug.h"

Lecture::Lecture() 
    : adresse_(0x0000), donnee_(0), instruction_(0b00), 
    operande_(0b00), adresseBoucle_(0), del_(PORTA, PA0, PA1),
    programmeFini_(false)
{
    PontH::initialiserRegistre();
}

void Lecture::initialiserLecture()
{
    com_.initialisationUART();
}

void Lecture::faireInstruction(uint8_t instruction, uint8_t operande)
{
    switch (instruction) {
        case ATTENDRE:
            for (uint8_t i = 0; i < operande; i++) {
                _delay_ms(25);
            }
            break;
        
        case ALLUMER_LED:
            if (operande == 1) {
                del_.allumerCouleur(Del::Couleur::VERT);
            }
            else if (operande == 2) {
                del_.allumerCouleur(Del::Couleur::ROUGE);
            }
            else {
                del_.allumerCouleur(Del::Couleur::ETEINT);
            }

            break;

        case ETEINDRE_LED:
            del_.allumerCouleur(Del::Couleur::ETEINT);
            break;

        case JOUER_SON:
            break;

        case ARRETER_SON:
            break;

        case ARRETER_MOTEURS_1:
        case ARRETER_MOTEURS_2:
           PontH::arreter();
            break;
            
        case AVANCER:
            PontH::initialiserRegistre();

            PontH::avancer(((uint16_t)operande * 100) / 255);
            
            break;

        case RECULER:
            PontH::reculer(((uint16_t)operande * 100) / 255);
            break;

        case TOURNER_DROITE:
            PontH::initialiserRegistre();
            PontH::tournerDroite(255); 
            _delay_ms(600); 
            PontH::arreter();
            break;

        case TOURNER_GAUCHE:
            PontH::initialiserRegistre();
            PontH::tournerGauche(250); 
            _delay_ms(450); 
            PontH::arreter();
            break;

        case DEBUT_BOUCLE:
            adresseBoucle_ = adresse_;
            compteurBoucle_ = operande;
            break;
        
        case FIN_BOUCLE:
            if (compteurBoucle_ != 0) {
                compteurBoucle_--;
                adresse_ = adresseBoucle_;
            }
            break;

        case FIN:
            PontH::arreter();
            del_.allumerCouleur(Del::Couleur::ETEINT);
            programmeFini_ = true;
            break;
    }
}

void Lecture::lireMemoire()
{
    
    // TEMPORAIRE - vérification mémoire
    //for (uint16_t i = 0; i < 12; i++) {
        //uint8_t donnee;
        //mem_.lecture(i, &donnee);
    //DEBUG_PRINT(com_, "addr %d = 0x%02X\r\n", i, donnee);
    //}
    
    
    mem_.lecture(adresse_++, &donnee_);
    uint16_t taille = donnee_;
    mem_.lecture(adresse_++, &donnee_);
    taille = (taille << 8) | donnee_;



    bool estDebutTrouve = false;

    while(adresse_ < taille && !programmeFini_) {
        mem_.lecture(adresse_++, &instruction_);
        mem_.lecture(adresse_++, &operande_);
        //com_.transmissionFormatee("inst=0x%02X op=0x%02X\r\n", instruction_, operande_);



        if (!estDebutTrouve) {
            if (instruction_ == DEBUT) {
                estDebutTrouve = true;
            }
            continue;
        }
        faireInstruction(instruction_, operande_);

    }        
}





