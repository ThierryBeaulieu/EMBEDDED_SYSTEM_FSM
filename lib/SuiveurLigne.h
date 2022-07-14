/*
 * Projet final
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 *
 * Description: Cette classe implemente le suiveur de ligne connecte au portA
 *
 */

#ifndef SUIVEURDELIGNE_H
#define SUIVEURDELIGNE_H

#include <avr/io.h>
#include <sys/types.h>
#include <util/delay.h>

#include "Lcd.h"
#include "Moteur.h"
#include "Etat.h"
#include "Uart.h"

class SuiveurLigne {
public:
  const uint8_t ENTREE = 0x00;
  const int VITESSE_MAX = 60;
  const int VITESSE_MOY = 50;
  const int VITESSE_MIN = 0;
  const int VITESSE_GAUCHE_OFFSET = 60;
  const int OFFSET = 5;
  
  enum Detection { COIN_GAUCHE = 0, COIN_DROIT = 1, NORMAL = 2 };

public:
  SuiveurLigne();

  void miseAJourEtatInterne();
  void miseAJourSenseurs();

  void setEtatGlobal(Etat etat);
  void setDetection(Detection etat);

  void activerSL(bool etat);

  void setVitesse();
  void suivreLigne(Moteur moteur);

  void setCoinDetecte(bool etat);
  bool getCoinDetecte();

  void setAligne(bool etat);
  bool getAligne();

  void setLigneDetecte(bool etat);
  bool getLigneDetecte();

private:
  bool estEnMarche_;
  bool coinDetecte_  = false;
  bool aligne_       = false;
  bool ligneDetecte_ = false;

  uint8_t senseurs_;
  int vitesseDroit_;
  int vitesseGauche_;

  Detection detecteur_ = Detection::NORMAL;
  Etat etat_ = Etat::AVANCER_A_B;
  Lcd lcd;
  Uart uart;
};
#endif /* SUIVEURDELIGNE_H */
