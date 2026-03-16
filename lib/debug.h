#pragma once
#include "Communication.hpp"

#ifdef DEBUG
    #define DEBUG_PRINT(comm, format, ...) comm.transmissionFormatee(format, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(comm, format, ...) do {} while (0)
#endif