#include "rapport.hpp"
#include "memoire_24.h"
#include "../lib/Del.hpp"
#include <util/delay.h>


// addr memoire a recalibrer!!!
#define ADR_LOCAL_A      0x1000
#define ADR_LOCAL_B      0x1001
#define ADR_LOCAL_C      0x1002
#define ADR_LOCAL_D      0x1003
#define ADR_COU_EST      0x1004
#define ADR_COU_OUEST    0x1005
#define ADR_SIGNATURE    0x1006

void sauvegarderRapport(uint8_t nPersonnesLocalA,
                        uint8_t nObjetsLocalB,
                        uint8_t nObjetsLocalC,
                        uint8_t nPersonnesLocalD,
                        uint8_t nZonesEndommageesCouloirEst,
                        uint8_t nZonesEndommageesCouloirOuest)
{
    Memoire24CXXX memoire;

    memoire.ecriture(ADR_LOCAL_A, nPersonnesLocalA);
    _delay_ms(10);
    memoire.ecriture(ADR_LOCAL_B, nObjetsLocalB);
    _delay_ms(10);
    memoire.ecriture(ADR_LOCAL_C, nObjetsLocalC);
    _delay_ms(10);
    memoire.ecriture(ADR_LOCAL_D, nPersonnesLocalD);
    _delay_ms(10);
    memoire.ecriture(ADR_COU_EST, nZonesEndommageesCouloirEst);
    _delay_ms(10);
    memoire.ecriture(ADR_COU_OUEST, nZonesEndommageesCouloirOuest);
    _delay_ms(10);
    memoire.ecriture(ADR_SIGNATURE, 0xA5);
    _delay_ms(10);
}

bool lireRapport(uint8_t& nPersonnesLocalA,
                 uint8_t& nObjetsLocalB,
                 uint8_t& nObjetsLocalC,
                 uint8_t& nPersonnesLocalD,
                 uint8_t& nZonesEndommageesCouloirEst,
                 uint8_t& nZonesEndommageesCouloirOuest)
{
    Memoire24CXXX memoire;
    uint8_t signature = 0;

    memoire.lecture(ADR_SIGNATURE, &signature);

    if (signature != 0xA5) return false;

    memoire.lecture(ADR_LOCAL_A, &nPersonnesLocalA);
    memoire.lecture(ADR_LOCAL_B, &nObjetsLocalB);
    memoire.lecture(ADR_LOCAL_C, &nObjetsLocalC);
    memoire.lecture(ADR_LOCAL_D, &nPersonnesLocalD);
    memoire.lecture(ADR_COU_EST, &nZonesEndommageesCouloirEst);
    memoire.lecture(ADR_COU_OUEST, &nZonesEndommageesCouloirOuest);

    return true;
}

void ecrireLigne(Communication& com, bool conformite, const char* nom, uint8_t nombre, const char* detail)
{
    if (conformite)
        com.transmissionFormatee("%-20s oui\r\n", nom);
    else
        com.transmissionFormatee("%-20s non             %d %s\r\n", nom, nombre, detail);
}

void genererRapport(uint8_t nPersonnesLocalA, uint8_t nObjetsLocalB, uint8_t nObjetsLocalC, uint8_t nPersonnesLocalD,
                    uint8_t nZonesEndommageesCouloirEst, uint8_t nZonesEndommageesCouloirOuest)
{
    Communication com;
    com.initialisationUART();
    bool conformiteA = (nPersonnesLocalA == 0);
    bool conformiteB = (nObjetsLocalB == 0);
    bool conformiteC = (nObjetsLocalC == 0);
    bool conformiteD = (nPersonnesLocalD == 0);
    bool conformiteEst = (nZonesEndommageesCouloirEst == 0);
    bool conformiteOuest = (nZonesEndommageesCouloirOuest == 0);

    _delay_ms(1000);

    com.transmissionFormatee("Rapport de conformite\r\n\n");
    com.transmissionFormatee("%-20s %-15s %s\r\n", "Emplacement", "conformite", "detail");
    com.transmissionOccurence('-', 55);
    com.transmissionFormatee("\r\n");

    ecrireLigne(com, conformiteA,    "Local A",       nPersonnesLocalA,          "personnes");
    ecrireLigne(com, conformiteB,    "Local B",       nObjetsLocalB,             "objet");
    ecrireLigne(com, conformiteC,    "Local C",       nObjetsLocalC,             "objets");
    ecrireLigne(com, conformiteD,    "Local D",       nPersonnesLocalD,          "personnes");
    ecrireLigne(com, conformiteOuest,"Couloir OUEST", nZonesEndommageesCouloirOuest, "zones endommagees");
    ecrireLigne(com, conformiteEst,  "Couloir EST",   nZonesEndommageesCouloirEst,   "zones endommagees");
}

void genererRapportDepuisMemoire()
{
    Del del(PORTC, PC6, PC7);

    for (uint8_t i = 0; i < 8; i++)
    {
        del.allumerCouleur(Del::Couleur::ROUGE);
        _delay_ms(125);
        del.allumerCouleur(Del::Couleur::ETEINT);
        _delay_ms(125);
    }

    uint8_t localA = 0;
    uint8_t localB = 0;
    uint8_t localC = 0;
    uint8_t localD = 0;
    uint8_t couloirEst = 0;
    uint8_t couloirOuest = 0;

    lireRapport(localA, localB, localC, localD, couloirEst, couloirOuest);
    genererRapport(localA, localB, localC, localD, couloirEst, couloirOuest);
    
}