/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Ce programme implemente un CTC sur le Timer#2 (TCNT2).
*/

#ifndef PWMT2_H
#define PWMT2_H

#include <avr/io.h>

enum PrescaleurTimer2{
    T2_P1       = (0 << CS22) | (0 << CS21) | (1 << CS20),  // clk/1 (Aucun prescaling)
    T2_P8       = (0 << CS22) | (1 << CS21) | (0 << CS20),  // clk/8
    T2_P32      = (0 << CS22) | (1 << CS21) | (1 << CS20),  // clk/32
    T2_P64      = (0 << CS22) | (1 << CS21) | (1 << CS20),  // clk/64
    T2_P128     = (0 << CS22) | (1 << CS21) | (1 << CS20),  // clk/128
    T2_P256     = (1 << CS22) | (0 << CS21) | (0 << CS20),  // clk/256
    T2_P1024    = (1 << CS22) | (0 << CS21) | (1 << CS20),  // clk/1024
};

void initializationCtc(PrescaleurTimer2 prescaleur);

void demarrerCtc();
void arreterCtc();

void ajusterCtc(uint8_t comparaisonA);
#endif /* PWMT2_H */