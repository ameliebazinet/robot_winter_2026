enum Etat 
{
    SORTIR_STATIONNEMENT,

    PREMIER_COULOIR_SUD,
    PREMIER_COULOIR_LONG,

    COULOIR_NORD,
    PIECE_A_D,
    PIECE_B_C,

    DERNIER_COULOIR_LONG,
    DERNIER_COULOIR_SUD,

    ENTRER_STATIONNEMENT
};

void suivreCouloir();
void sortirStationnement();
void parcourirCouloir();
void scanPoteaux() {};
void compterPersonnes();
void entrerStationnement();
void faireExecution();