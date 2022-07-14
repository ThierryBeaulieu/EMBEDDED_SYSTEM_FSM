/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Ce programme implemente un PWM phase correct mode 1 
 * sur le Timer#0 (TCNT0).
*/

#include "PWM_T0.h"

/**
 * fixe la valeur des registres du Timer0 pour implementer
 * un PWM phase correct mode 1
 * @param  prescaleur   enum du prescale a appliquer 
 * @return void
*/
void initializationPwm(PrescaleurTimer0 prescaleur){
    // Initialiser les registres du timer0 a zero
    TCCR0A = 0;
    TCCR0B = 0;

    // Efface OC0A sur Compare Match lors du comptage.
    // Definir OC0A sur Compare Match lors du décomptage.
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0);
	
    // Efface OC0B sur Compare Match lors du comptage.
    // Definir OC0B sur Compare Match lors du décomptage.
	TCCR0A |= (1 << COM0B1) | (0 << COM0B0);
	
    // PWM, Phase Correct mode 1
	TCCR0A |= (0 << WGM01) | (1 << WGM00);
	
    // On configure le prescale
    TCCR0B |= prescaleur;
}

/**
 * Definit la valeur
 * @param  comparaisonA     valeur du registre de comparaison de sortie A (moteur droit)
 * @param  comparaisonB     valeur du registre de comparaison de sortie B (moteur gauche)
 * @return void
*/
void ajustementPwm(uint8_t comparaisonA, uint8_t comparaisonB){
    OCR0A = comparaisonA;
    OCR0B = comparaisonB;
}