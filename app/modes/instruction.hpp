// #include "../lecture/lecture.hpp"

// void faireInstruction()
// {
//     // siganlement du début 
//     for (uint8_t i = 0; i < 8; i++)
//     {
//         del_.allumerCouleur(Del::Couleur::VERT); 
//         _delay_ms(125); 
//         del_.allumerCouleur(Del::Couleur::ETEINT); 
//         _delay_ms(125); 
//     }
//     lireMemoire(); 
//     for(uint8_t i = 0; i < 3; i++) {
//         Son::jouer(note_[i]);
//         _delay_ms(250); 
//         Son::arreter();
//         _delay_ms(125); 
//     }

//     _delay_ms(DELAI_2_SECONDES); 
//     if(directionHoraire_){
//         // allumer vert
//         del_.allumerCouleur(Del::Couleur::VERT); 
//         _delay_ms(DELAI_2_SECONDES); 
//     }
//     else {
//         del_.allumerCouleur(Del::Couleur::ROUGE); 
//         _delay_ms(DELAI_2_SECONDES); 
//     }

//     _delay_ms(DELAI_2_SECONDES);

//     // allumer la del ambre : 

//     for(uint8_t i = 0; i < valeurAtt_; i++)
//     {
//         del_.allumerCouleurAmbre(); 
//         _delay_ms(DELAI_CLIGNOTEMENT_AMBRE); 
//         del_.allumerCouleur(Del::Couleur::ETEINT); 
//         _delay_ms(DELAI_CLIGNOTEMENT_AMBRE); 
//     }


// }