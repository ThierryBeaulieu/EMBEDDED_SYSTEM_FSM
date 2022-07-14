/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 *
 * Description: Ce programme implemente un piezo pour jouer des notes et melodies
 */

#include "Sonorite.h"

const uint16_t DELAI = 150;

/**
 * Constructeur par parametre de l'objet Sonorite
 * @param  void
 */
Sonorite::Sonorite()
{
    initializationCtc(PrescaleurTimer2::T2_P256);
}

/**
 * Joue une note
 * @param  note de type enum Note
 * @return void
 */
void Sonorite::jouerNote(uint8_t note)
{
    demarrerCtc();
    ajusterCtc(note);
}

/**
 * Cesse le son
 * @param  void
 * @return void
 */
void Sonorite::arreter()
{
    arreterCtc();
}