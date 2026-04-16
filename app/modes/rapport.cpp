#include "rapport.hpp"
#include "memoire_24.h"


// addr memoire a recalibrer!!!
#define ADR_LOCAL_A      0x0000
#define ADR_LOCAL_B      0x0001
#define ADR_LOCAL_C      0x0002
#define ADR_LOCAL_D      0x0003
#define ADR_COU_EST      0x0004
#define ADR_COU_OUEST    0x0005
#define ADR_SIGNATURE    0x0006

void sauvegarderRapport(uint8_t nPersonnesLocalA,
                        uint8_t nObjetsLocalB,
                        uint8_t nObjetsLocalC,
                        uint8_t nPersonnesLocalD,
                        uint8_t nZonesEndommageesCouloirEst,
                        uint8_t nZonesEndommageesCouloirOuest)
{
    Memoire24CXXX memoire;

    memoire.ecriture(ADR_LOCAL_A, nPersonnesLocalA);
    memoire.ecriture(ADR_LOCAL_B, nObjetsLocalB);
    memoire.ecriture(ADR_LOCAL_C, nObjetsLocalC);
    memoire.ecriture(ADR_LOCAL_D, nPersonnesLocalD);
    memoire.ecriture(ADR_COU_EST, nZonesEndommageesCouloirEst);
    memoire.ecriture(ADR_COU_OUEST, nZonesEndommageesCouloirOuest);
    memoire.ecriture(ADR_SIGNATURE, 0xA5);
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
        com.transmissionFormatee("%s :\t oui \r\n", nom);
    else
        com.transmissionFormatee("%s :\t\t non\t\t %d %s\r\n", nom, nombre, detail);
}

void genererRapport(uint8_t nPersonnesLocalA, uint8_t nObjetsLocalB, uint8_t nObjetsLocalC, uint8_t nPersonnesLocalD,
                    uint8_t nZonesEndommageesCouloirEst, uint8_t nZonesEndommageesCouloirOuest)
{
    Communication com;
    bool conformiteA = (nPersonnesLocalA == 0);
    bool conformiteB = (nObjetsLocalB == 0);
    bool conformiteC = (nObjetsLocalC == 0);
    bool conformiteD = (nPersonnesLocalD == 0);
    bool conformiteEst = (nZonesEndommageesCouloirEst == 0);
    bool conformiteOuest = (nZonesEndommageesCouloirOuest == 0);

    com.transmissionFormatee("Emplacement \t\t Conformite \t\t detail \r\n");
    com.transmissionOccurence('-', 15);
    com.transmissionFormatee("\r\n");

    ecrireLigne(com, conformiteA, "Local A", nPersonnesLocalA, "personnes");
    ecrireLigne(com, conformiteB, "Local B", nObjetsLocalB, "objets");
    ecrireLigne(com, conformiteC, "Local C", nObjetsLocalC, "objets");
    ecrireLigne(com, conformiteD, "Local D", nPersonnesLocalD, "personnes");
    ecrireLigne(com, conformiteOuest, "Couloir OUEST", nZonesEndommageesCouloirOuest, "zones endommagees");
    ecrireLigne(com, conformiteEst, "Couloir EST", nZonesEndommageesCouloirEst, "zones endommagees");
}

void genererRapportDepuisMemoire()
{
    uint8_t localA = 0;
    uint8_t localB = 0;
    uint8_t localC = 0;
    uint8_t localD = 0;
    uint8_t couloirEst = 0;
    uint8_t couloirOuest = 0;

    if (!lireRapport(localA, localB, localC, localD, couloirEst, couloirOuest))
        return;

    genererRapport(localA, localB, localC, localD, couloirEst, couloirOuest);
}





