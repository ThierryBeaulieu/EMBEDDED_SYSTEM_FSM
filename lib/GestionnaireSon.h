/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 * 
 * Description: Ce programme implemente le gestionnaire de sonorite 
*/

#ifndef GESTIONNAIRE_SON_H
#define GESTIONNAIRE_SON_H

#include "Sonorite.h"

#include <avr/io.h>
#include <util/delay.h>

class GestionnaireSon {
public:
  const uint8_t BORNE_INF    = 30;   // 12" = 30.48cm
  const uint8_t BORNE_SUP    = 61;   // 24" = 60.96cm

  // obtenue a l'aide de l'equation suivante:
  // ((fClk / frequence) / 2 / prescaleur) - 1
  const uint8_t NOTE_BORNE_INF      = 7;    // 2000Hz
  const uint8_t NOTE_BORNE_SUP      = 77;   // 200Hz

  // ratio = 77 - 7 / 61 - 30
  const uint8_t RATIO_INTERPOLATION = 2;   // 2.25

public:
  GestionnaireSon(Sonorite son);
  void distanceANote(uint8_t distance);
  Sonorite son;

private:
  uint8_t interpollation(uint8_t distance);
};

#endif /* GESTIONNAIRE_SON_H */