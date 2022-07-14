/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Cette classe implemente un objet moteur qui utilise 2 moteurs 
 * DC (1 moteur pour chaque roue du robot). les moteur operent en PWM phase
 * correct (mode 1) sur le Timer#0.
 * 
 * Identifications matérielles: B3 <=> D moteur#1
 *                              B4 <=> E moteur#1
 *                              B5 <=> E moteur#2
 *                              B6 <=> D moteur#2
*/

#ifndef MOTEUR_H
#define MOTEUR_H

#include "PWM_T0.h"

#include <avr/io.h>
#include <math.h>
#include <sys/types.h>
#include <util/delay.h>

class Moteur
{
public:
  enum Direction
  {
    NEG = 0,       // negative (vers l'arriere)
    POS = 1,       // positive (vers l'avant)
    POS_ET_NEG = 2, // à la fois positif et à la fois négatif (tourne sur lui-même)
    NEG_ET_POS = 3
  };

public:
  const uint8_t SORTIE = 0xff;
  const uint8_t VITESSE_MIN = 0x0000; // 0
  const uint8_t VITESSE_MAX = 0x00FF; // 255

  const uint8_t POURCENTAGE_MIN = 0;
  const uint8_t POURCENTAGE_MAX = 100;

  const uint8_t DELAI_TOURNER = 4;

public:
  Moteur(PrescaleurTimer0 prescaleur = PrescaleurTimer0::T0_P8);

  void pause(int nbrIteration);

  void definirVitesse(int pourcentageDroit, int pourcentageGauche);
  void definirVitesse(int pourcentage);

  void definirDirection(Direction direction);

  void avancer(int pourcentageDroit, int pourcentageGauche);
  void reculer(int pourcentageDroit, int pourcentageGauche);

  void avancer(int pourcentage);
  void reculer(int pourcentage);

  void tournerDroit(int pourcentage); // Tourne légèrement à droite.
  void tournerGauche(int pourcentage); // Tourne légèrement à gauche.

  void tourner90Droit();
  void tourner90Gauche();
  void tourner90Poteau();

  void tournerSurLuiMeme();

  void tourner145Degrees();
  void tourner35Degrees();

  void tourner45Degrees();
  void tournerMoins45Degrees();

  void contournerPoteau();

  void arreter();

private:
  uint8_t vitesseDroit_ = VITESSE_MIN;
  uint8_t vitesseGauche_ = VITESSE_MIN;

  Direction direction_ = POS;
};
#endif /* MOTEUR_H */
