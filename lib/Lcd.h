/*
 * Travail : Projet finale
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme gère l'affichage des données du LCD
 */
#ifndef LCD_H
#define LCD_H

#include <stdlib.h>
#include "Lcm_so1602dtr_m_fw.h"
#include "Customprocs.h"
#include "Gestionnaire.h"
#include <avr/io.h>

class Lcd
{

public:
    Lcd();
    void afficherNombreEnCm(float nombreAAfficherEnCm); // Affiche un nombre suivit d'une unité Cm
    void afficherNombreEnPo(float nombreAAfficherEnPo); // Affiche un nombre suivit d'une unité Po
    void effacer();

private:
    const uint8_t largeurMinimaleDonnee = 1;
    const uint8_t nbreChiffresApresVirgule = 1;
    const uint8_t indexMessage = 0;
    const bool effacerAncienAffichage = true;
    char resultats[15];

private:     
    void afficherNombre(float donnee);
    
private:
    LCM *afficheur_;    
};
#endif // LCD_H