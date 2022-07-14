/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Ce programme implemente un PWM phase correct mode 1 
 * sur le Timer#0 (TCNT0).
*/

#ifndef PWMT0_H
#define PWMT0_H

#include <avr/io.h>

enum PrescaleurTimer0{
    T0_P1       = (0 << CS02) | (0 << CS01) | (1 << CS00),  // clk/1 (Aucun prescaling)
    T0_P8       = (0 << CS02) | (1 << CS01) | (0 << CS00),  // clk/8
    T0_P64      = (0 << CS02) | (1 << CS01) | (1 << CS00),  // clk/64
    T0_P256     = (1 << CS02) | (0 << CS01) | (0 << CS00),  // clk/256
    T0_P1024    = (1 << CS02) | (0 << CS01) | (1 << CS00),  // clk/1024
};

void initializationPwm(PrescaleurTimer0 prescaleur);
void ajustementPwm(uint8_t comparaisonA, uint8_t comparaisonB);

#endif /* PWMT0_H */