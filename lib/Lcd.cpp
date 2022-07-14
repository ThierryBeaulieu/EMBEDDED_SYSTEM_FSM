/*
 * Travail : Projet finale
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme gère l'affichage des données du LCD
 */
#include "Lcd.h"
Lcd::Lcd()
{
    afficheur_ = new LCM(&DDRC, &PORTC);
}

void Lcd::afficherNombre(float donnee)
{
    dtostrf(donnee, largeurMinimaleDonnee, nbreChiffresApresVirgule, resultats);
    afficheur_->write(resultats, indexMessage, effacerAncienAffichage);
}

void Lcd::afficherNombreEnCm(float donnee)
{
    this->afficherNombre(donnee);
    afficheur_->put(' ').put('c').put('m');
}

void Lcd::afficherNombreEnPo(float donnee)
{
    this->afficherNombre(donnee);
    afficheur_->put(' ').put('p').put('o');
}

void Lcd::effacer()
{
    afficheur_->clear();
}
