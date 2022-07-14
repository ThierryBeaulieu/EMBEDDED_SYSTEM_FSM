#ifndef INSTRUCTION_H
#define INSTRUCTION_H

enum class Instruction
{
    DEBUT               = 0b00000001,   // dbt
    ATTENDRE            = 0b00000010,   // att
    ALLUMER_DEL         = 0b01000100,   // dal
    ETEINDRE_DEL        = 0b01000101,   // det
    JOUER_SONORITE      = 0b01001000,   // sgo
    ARRETE_SONORITE     = 0b00001001,   // sar
    ARRETE_MOTEUR_1     = 0b01100000,   // mar
    ARRETE_MOTEUR_2     = 0b01100001,   // mar
    AVANCER             = 0b01100010,   // mav
    RECULER             = 0b01100011,   // mre
    TOURNER_A_DROITE    = 0b01100100,   // trd
    TOURNER_A_GAUCHE    = 0b01100101,   // trg
    DEBUT_DE_BOUCLE     = 0b11000000,   // dbc
    FIN_DE_BOUCLE       = 0b11000001,   // fbc
    FIN                 = 0b11111111    // fin

};

#endif /* INSTRUCTION_H */