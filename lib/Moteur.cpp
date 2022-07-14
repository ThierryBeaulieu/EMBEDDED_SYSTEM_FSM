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

#include "Moteur.h"
#include "PWM_T0.h"
#include <sys/types.h>

const uint16_t DELAI = 150;

/**
 * Constructeur par parametre de l'objet Moteur
 * @param  prescaleur   enum du prescale a appliquer (se 
 *                      referer a Pwm.h pour les valeurs)
*/
Moteur::Moteur(PrescaleurTimer0 prescaleur)
{
  DDRB = SORTIE;
  initializationPwm(prescaleur);
}

/**
 * Fixe l'attribut vitesse_
 * @param   pourcentageDroit    valeur du pourcentage de vitesse :
 * @param   pourcentageGauche   entre 0% (0) et 100% (255)
 * @return void
*/
void Moteur::definirVitesse(int pourcentageDroit, int pourcentageGauche)
{
  vitesseDroit_ = static_cast<uint8_t>(pourcentageDroit * (VITESSE_MAX / 100.0));
  vitesseGauche_ = static_cast<uint8_t>(pourcentageGauche * (VITESSE_MAX / 100.0));
}

/**
 * Fixe l'attribut vitesse_
 * @param   pourcentage   valeur du pourcentage de vitesse :
 *                        entre 0% (0) et 100% (255)
 * @return void
*/
void Moteur::definirVitesse(int pourcentage)
{
  definirVitesse(pourcentage, pourcentage);
}

/**
 * Definit la direction des moteurs
 * @param  direction    enum de la direction :
 *                      POS (positive) et NEG (negative)
 * @return void
*/
void Moteur::definirDirection(Direction direction)
{
  direction_ = direction;

  if (direction_ == POS)
  {
    PORTB &= (~(1 << PB2));
    PORTB &= (~(1 << PB5));
  }
  else if (direction_ == POS_ET_NEG)
  {
    PORTB &= (~(1 << PB2));
    PORTB |= (1 << PB5);
  }
  else if (direction_ == NEG_ET_POS)
  {
    PORTB |= (1 << PB2);
    PORTB &= (~(1 << PB5));
  }
  else
  {
    PORTB |= (1 << PB2);
    PORTB |= (1 << PB5);
  }
}

/**
 * Permet d'appliquer un Delai variable
 * @param  nbrIteration  nombre d'iteration du delai a appliquer
 * @return void
*/
void Moteur::pause(int nbrIteration)
{
  for (int i = 0; i < nbrIteration; i++)
  {
    _delay_ms(DELAI);
  }
}

/**
 * Mouvement vers l'avant
 * @param   pourcentageDroit    valeur du pourcentage de vitesse :
 * @param   pourcentageGauche   entre 0% (0) et 100% (255)
 * @return void
*/
void Moteur::avancer(int pourcentageDroit, int pourcentageGauche)
{
  definirDirection(Direction::POS);
  definirVitesse(pourcentageDroit, pourcentageGauche);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
}

/**
 * Mouvement vers l'arriere
 * @param   pourcentageDroit    valeur du pourcentage de vitesse :
 * @param   pourcentageGauche   entre 0% (0) et 100% (255)
 * @return void
*/
void Moteur::reculer(int pourcentageDroit, int pourcentageGauche)
{
  definirDirection(Direction::NEG);
  definirVitesse(pourcentageDroit, pourcentageGauche);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
}

/**
 * Mouvement du robot sur lui-même
 * @param aucun
 * @return void
*/
void Moteur::tournerSurLuiMeme()
{
  uint8_t pourcentage = 90;
  definirDirection(Direction::POS_ET_NEG);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(1000);
  //this->arreter();
}

/**
 * Mouvement du robot d'un angle de 145 degrées
 * @param aucun
 * @return void
*/
void Moteur::tourner145Degrees()
{
  uint8_t pourcentage = 90;                             // WAS at 70
  definirDirection(Direction::POS_ET_NEG);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(800);                                      // WAS 700
  this->arreter();
}

void Moteur::tourner35Degrees()
{
  //uint8_t pourcentage = 90;
  definirDirection(Direction::POS_ET_NEG);
  definirVitesse(80, 90);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(600);
  this->arreter();
}

/**
 * Mouvement vers l'avant
 * @param   pourcentage   valeur du pourcentage de vitesse :
 *                        entre 0% (0) et 100% (255)
 * @return void
*/
void Moteur::avancer(int pourcentage)
{
  avancer(pourcentage, pourcentage);
}

/**
 * Mouvement vers l'arriere
 * @param   pourcentage   valeur du pourcentage de vitesse :
 *                        entre 0% (0) et 100% (255)
 * @return void
*/
void Moteur::reculer(int pourcentage)
{
  reculer(pourcentage, pourcentage);
}


/**
 * Contourner Poteau
 * @param  void
 *
 * @return void
*/
void Moteur::contournerPoteau()
{
  // d'abord tourner un angle de presque 45 degrees.
  uint8_t pourcentage = 80;
  definirDirection(Direction::POS_ET_NEG);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(250); // Diminuer ce Delay pour être capable d'avoir un angle plus petit.
  this->arreter();

  // Avance pendant un certain délais.
  this->avancer(pourcentage, pourcentage);
  _delay_ms(1900);

// tourner un angle de 45 degree pour qu'il reviens droit.
 definirDirection(Direction::NEG_ET_POS);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(250); // Modifier ce délais pour avoir un angle

// avancer pour un certain delai
    this->avancer(pourcentage, pourcentage);
  _delay_ms(1200);
/*
  definirDirection(Direction::POS_ET_NEG);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(450);
*/

}


  void Moteur::tourner45Degrees(){
    uint8_t pourcentage = 90;
    definirDirection(Direction::POS_ET_NEG);
    definirVitesse(pourcentage, pourcentage);
    ajustementPwm(vitesseDroit_, vitesseGauche_);
    _delay_ms(300); // 150 à 2 A, // 300 à 1.6 A
    this->arreter();
    _delay_ms(1000);
  }

void Moteur::tournerMoins45Degrees(){
  uint8_t pourcentage = 90;
  definirDirection(Direction::NEG_ET_POS);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(200);
  this->arreter();
}

/**
 * Rotation vers la droite
 * @param  pourcentage  valeur du pourcentage de vitesse
 * @return void
*/
void Moteur::tournerDroit(int pourcentage)
{
  definirDirection(Direction::POS);
  definirVitesse(pourcentage);
  ajustementPwm(VITESSE_MIN, vitesseDroit_);
}

/**
 * Rotation vers la gauche
 * @param  pourcentage  valeur du pourcentage de vitesse
 * @return void
*/
void Moteur::tournerGauche(int pourcentage)
{
  definirDirection(Direction::POS);
  definirVitesse(pourcentage);
  ajustementPwm(vitesseGauche_, VITESSE_MIN);
}

/**
 * Rotation vers la droite de 90 deg
 * @param  void
 * @return void
*/
void Moteur::tourner90Droit()
{
  uint8_t pourcentage = 70;
  definirDirection(Direction::NEG_ET_POS);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(420); // 420 à 1.6 A, 
  this->arreter();
}

void Moteur::tourner90Poteau()
{
  uint8_t pourcentage = 70;
  definirDirection(Direction::NEG_ET_POS);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(420); // 420 à 1.6 A, 
  this->arreter();
}

/**
 * Rotation vers la gauche de 90 deg
 * @param  void
 * @return void
*/
void Moteur::tourner90Gauche()
{
  uint8_t pourcentage = 70;
  definirDirection(Direction::POS_ET_NEG);
  definirVitesse(pourcentage, pourcentage);
  ajustementPwm(vitesseDroit_, vitesseGauche_);
  _delay_ms(420); // 420 à 1.6 A
  this->arreter();
}

/**
 * Arrete le mouvement des moteurs
 * @param  void
 * @return void
*/
void Moteur::arreter()
{
  ajustementPwm(VITESSE_MIN, VITESSE_MIN);
}