// Fichier : debug.h
// Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
// Description : Macro pour l'impression de messages de débogage.

#pragma once
#include "Communication.hpp"

#ifdef DEBUG
    #define DEBUG_PRINT(comm, format, ...) comm.transmissionFormatee(format, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(comm, format, ...) do {} while (0)
#endif