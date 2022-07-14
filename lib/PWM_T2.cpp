/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Ce programme implemente un CTC sur le Timer#2 (TCNT2).
*/

#include "PWM_T2.h"

/**
 * fixe la valeur des registres du Timer2 pour implementer un CTC
 * @param  prescaleur   enum du prescale a appliquer
 * @return void
*/
void initializationCtc(PrescaleurTimer2 prescaleur){
    // Initialiser les registres du timer2 a zero
    TCNT2 = 0;

    // Basculez OC2A en Compare Match
	TCCR2A &= ~(1 << COM2A0);
	
    // mode CTC
	TCCR2A |= (1 << WGM21);
	
    // On configure le prescale
    TCCR2B |= prescaleur;
}

/**
 * CTC demare
 * @return void
*/
void demarrerCtc(){
    TCCR2A |= (1 << COM2A0);
}

/**
 * CTC arrete
 * @return void
*/
void arreterCtc(){
    TCCR2A &= ~(1 << COM2A0);
}

/**
 * Definit la valeur
 * @param  comparaisonA
 * @return void
*/
void ajusterCtc(uint8_t comparaisonA){
    OCR2A = comparaisonA;
}

