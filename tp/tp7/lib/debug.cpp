// #include "../Headers/Communication.hpp"
// #include "../Headers/debug.h"


// void Communication::debugPrint(const char* msg) {
//     transmissionChaine(msg);
//     transmissionUART('\n');
// }

// void Communication::debugPrintInt(const char* msg, uint8_t val) {
//     transmissionChaine(msg);
//     // Convertit uint8_t en string sans printf ni STL
//     char buffer[4];
//     uint8_t i = 0;
//     if (val == 0) {
//         transmissionUART('0');
//     } else {
//         while (val > 0) {
//             buffer[i++] = '0' + (val % 10);
//             val /= 10;
//         }
//         for (int j = i - 1; j >= 0; j--)
//             transmissionUART((uint8_t)buffer[j]);
//     }
//     transmissionUART('\n');
// }