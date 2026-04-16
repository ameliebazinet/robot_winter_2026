#pragma once

#include <avr/io.h>
#include "Communication.hpp"

void sauvegarderRapport(uint8_t nPersonnesLocalA,
                        uint8_t nObjetsLocalB,
                        uint8_t nObjetsLocalC,
                        uint8_t nPersonnesLocalD,
                        uint8_t nZonesEndommageesCouloirEst,
                        uint8_t nZonesEndommageesCouloirOuest);

bool lireRapport(uint8_t& nPersonnesLocalA,
                 uint8_t& nObjetsLocalB,
                 uint8_t& nObjetsLocalC,
                 uint8_t& nPersonnesLocalD,
                 uint8_t& nZonesEndommageesCouloirEst,
                 uint8_t& nZonesEndommageesCouloirOuest);

void ecrireLigne(Communication& com,
                 bool conformite,
                 const char* nom,
                 uint8_t nombre,
                 const char* detail);

void genererRapport(uint8_t nPersonnesLocalA,
                    uint8_t nObjetsLocalB,
                    uint8_t nObjetsLocalC,
                    uint8_t nPersonnesLocalD,
                    uint8_t nZonesEndommageesCouloirEst,
                    uint8_t nZonesEndommageesCouloirOuest);

void genererRapportDepuisMemoire();