/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Ce programme implemente un piezo pour jouer des notes et melodies
*/

#ifndef SONORITE_H
#define SONORITE_H

#include "PWM_T2.h"

#include <avr/io.h>
#include <util/delay.h>

class Sonorite{
public:
    Sonorite();
    
    void jouerNote(uint8_t note);
    void arreter();
};

#endif /* SONORITE_H */
