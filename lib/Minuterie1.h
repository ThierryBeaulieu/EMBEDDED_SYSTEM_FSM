/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme implémente le Timer1 en mode CTC
 */

#include <avr/io.h>

#ifndef Minuterie1_H
#define Minuterie1_H

const uint16_t valeurPrescaler = 1024;

class Minuterie1
{
public:
    Minuterie1();
    ~Minuterie1();
    
    void partirChrono();
    void terminerChrono();

    void partirMinuterie(float dureeSeconde);
    
private:
    void arreterMinuterie();

};
#endif // Minuterie1_H