/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme implémente le Timer1 en mode CTC
 */

#include "Minuterie1.h"

/**
 * Constructeur
 */
Minuterie1::Minuterie1() {}

/**
 * Destructeur
 */
Minuterie1::~Minuterie1() {}

/**
 * Active le Timer1 du microcontrolleur et génère une interruption après la durée définie.
 * On utilise le mode CTC du timer 1 avec un prescaler de 1024.
 *
 * @param dureeSeconde durée en secondes avant l'interruption
 * @return void
 */
void Minuterie1::partirMinuterie(float dureeSeconde)
{
    arreterMinuterie();

    uint16_t nombreCycles = static_cast<uint16_t>((F_CPU / valeurPrescaler) * dureeSeconde);

    // Valeur initiale
    TCNT1 = 0;

    // Valeur déclenchant l'interruption
    OCR1A = nombreCycles;

    // Initialiser des registres du Timer1 a zero d'où on n'utilise pas
    TCCR1A = 0;
    TCCR1C = 0;

    // Set Mode CTC p.130
    // Prescaler = 1024 p.131
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (0 << CS11) | (1 << CS10);

    // Activer la comparaison avec OCR1A
    TIMSK1 |= (1 << OCIE1A);
}

void Minuterie1::partirChrono()
{
    this->partirMinuterie(0.5);

}

void Minuterie1::terminerChrono()
{
    this->arreterMinuterie();
}

void Minuterie1::arreterMinuterie()
{
    TIMSK1 = (0 << OCIE1A);
}