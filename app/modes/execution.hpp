#pragma once 
#include <avr/io.h>
#define F_CPU 8000000UL
#include "PontH.hpp"
#include "CapteurLigne.hpp"
#include "../lib/CapteurInfra.hpp"
#include "Del.hpp"
#include "../lecture/lecture.hpp"
#include "rapport.hpp"
#include "Communication.hpp"
#include <util/delay.h>

// Table d'etats de la machine à états de l'execution (Etat):
//
// +----------------------+--------------------------------------------+----------------------+
// | État présent         | Condition de transition                    | État suivant         |
// +----------------------+--------------------------------------------+----------------------+
// | SORTIR_STATIONNEMENT | toujours                                   | COULOIR_COTE         |
// | COULOIR_COTE         | toujours                                   | COULOIR_NORD         |
// | COULOIR_NORD         | compteurPiecesNord == 1 ou 4               | SALLE_A_D            |
// | COULOIR_NORD         | compteurPiecesNord == 2 ou 3               | SALLE_B_C            |
// | SALLE_A_D            | compteurPiecesNord < 4                     | COULOIR_NORD         |
// | SALLE_A_D            | compteurPiecesNord == 4                    | DERNIER_COULOIR_COTE |
// | SALLE_B_C            | toujours                                   | COULOIR_NORD         |
// | DERNIER_COULOIR_COTE | toujours                                   | ENTRER_STATIONNEMENT |
// | ENTRER_STATIONNEMENT | toujours                                   | (execution terminee) |
// +----------------------+--------------------------------------------+----------------------+

enum Etat
{
    SORTIR_STATIONNEMENT,
    COULOIR_COTE,

    COULOIR_NORD,
    SALLE_A_D,
    SALLE_B_C,

    DERNIER_COULOIR_COTE,
    ENTRER_STATIONNEMENT
};


// Table d'états de la machine à états de couloirNord (EtatCouloir) :
//
// +--------------------+-----------------------------------------------------+--------------------+
// | État présent       | Condition de transition                             | État suivant       |
// +--------------------+-----------------------------------------------------+--------------------+
// | COULOIR            | aucun capteur allumé (couloir vide)                 | VERIFICATION_ENTREE|
// | VERIFICATION_ENTREE| capteur côté mur allumé (fausse entrée)             | COULOIR            |
// | VERIFICATION_ENTREE| capteur côté mur éteint (vraie entrée détectée)     | ENTREE_TROUVEE     |
// | ENTREE_TROUVEE     | toujours (avance dans la salle et retourne)         | (retour)           |
// +--------------------+-----------------------------------------------------+--------------------+

enum EtatCouloir {
    COULOIR,
    VERIFICATION_ENTREE,
    ENTREE_TROUVEE
};

void recalibrer(); 
void recalibrerVirage(Lecture& l);
void suivreCouloir(uint8_t& nZones);
void tournerBoutCouloir(Lecture& l);
void sortirStationnement(Lecture& l);
void parcourirCouloir();
void executerSallesAD(uint8_t& nPersonnesLocal, Lecture& l);
void executerSallesBC(uint8_t& nObjetsLocal, volatile bool & tempsEcoule, Lecture& l);
void couloirNord(Lecture& l);
void entrerStationnement(Lecture& l);
void tournerDroite();
void faireExecution(uint8_t& nPersonnesLocalA,
                    uint8_t& nObjetsLocalB,
                    uint8_t& nObjetsLocalC,
                    uint8_t& nPersonnesLocalD,
                    uint8_t& nZonesEndommageesCouloirEst, 
                    uint8_t& nZonesEndommageesCouloirOuest,
                    volatile bool& tempsEcoule);