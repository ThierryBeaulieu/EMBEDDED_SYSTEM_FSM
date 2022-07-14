/*
 * Projet final
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 *
 * Description: Cette classe implemente le suiveur de ligne
 *
 */

#include "SuiveurLigne.h"

const uint8_t DELAI_SL = 150;

SuiveurLigne::SuiveurLigne()
{
  
  DDRA = ENTREE;
}

void pauseSL(int interation)
{
  for (int i = 0; i < interation; i++)
  {
    _delay_ms(DELAI_SL);
  }
}

void SuiveurLigne::miseAJourSenseurs()
{
  senseurs_ = PINA & 0b11111;
}

void SuiveurLigne::setEtatGlobal(Etat etat)
{
  etat_ = etat;
}

void SuiveurLigne::setDetection(Detection detecteur)
{
  detecteur_ = detecteur;
}

void SuiveurLigne::activerSL(bool etat)
{
  estEnMarche_ = etat;
}

void SuiveurLigne::setVitesse()
{
  switch (senseurs_)
  {
  case 0b00000:

    if (etat_ == Etat::AVANCER_A_B)
    {
      vitesseDroit_ = VITESSE_MAX;
      vitesseGauche_ = VITESSE_MAX;
      break;
    }
    if (detecteur_ == Detection::COIN_DROIT)
    {
      vitesseDroit_ = VITESSE_MIN;
      vitesseGauche_ = VITESSE_MOY;
      break;
    }
    else if (detecteur_ == Detection::COIN_GAUCHE)
    {
      vitesseDroit_ = VITESSE_MOY;
      vitesseGauche_ = VITESSE_MIN;
      break;
    }
    else
    {
      vitesseDroit_ = VITESSE_MIN;
      vitesseGauche_ = VITESSE_MIN;
      break;
    }

  case 0b11111:
    vitesseDroit_ = VITESSE_MIN;
    vitesseGauche_ = VITESSE_MIN + OFFSET;
    break;

  case 0b10000:
    vitesseDroit_ = VITESSE_MIN;
    vitesseGauche_ = VITESSE_MAX + OFFSET;
    break;

  case 0b11000:
    if (etat_ == Etat::AVANCER_A_B /*|| etat_ == Etat::AVANCER_B_C*/)
    {
      vitesseDroit_ = VITESSE_MOY;
      vitesseGauche_ = VITESSE_MAX + OFFSET;
      detecteur_ = Detection::COIN_DROIT;
      coinDetecte_ = true;
      break;
    }
    vitesseDroit_ = 10;
    vitesseGauche_ = VITESSE_MAX + OFFSET;
    detecteur_ = Detection::COIN_DROIT;
    break;

  case 0b11100:
  case 0b11010:
  case 0b11110:
  
    vitesseDroit_ = VITESSE_MOY;
    vitesseGauche_ = VITESSE_MAX + OFFSET;
    detecteur_ = Detection::COIN_DROIT;
    coinDetecte_ = true;
    pauseSL(1);
    break;

  case 0b01000:
    vitesseDroit_ = VITESSE_MOY;
    vitesseGauche_ = VITESSE_MAX + OFFSET;
    break;

  case 0b01100:
    vitesseDroit_ = 40;
    vitesseGauche_ = VITESSE_MAX + OFFSET;
    break;

  case 0b01110:
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = VITESSE_MAX;
    break;

  case 0b00100:
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = VITESSE_MAX+ OFFSET;
    break;

  case 0b00110:
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = 40;
    break;

  case 0b00010:
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = VITESSE_MOY;
    break;

  case 0b00111:
  case 0b01011:
  case 0b01111:
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = VITESSE_MOY;
    detecteur_ = Detection::COIN_GAUCHE;
    coinDetecte_ = true;
    pauseSL(1);
    break;

  case 0b00011:
    if (etat_ == Etat::AVANCER_MUR_C /*|| etat_ == Etat::AVANCER_C_B*/)
    {
      vitesseDroit_ = VITESSE_MAX;
      vitesseGauche_ = VITESSE_MOY;
      detecteur_ = Detection::COIN_GAUCHE;
      coinDetecte_ = true;
      break;
    }
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = 10;
    detecteur_ = Detection::COIN_GAUCHE;
    break;

  case 0b00001:
    vitesseDroit_ = VITESSE_MOY;
    vitesseGauche_ = VITESSE_MIN + OFFSET;
    break;

  default:
    vitesseDroit_ = VITESSE_MAX;
    vitesseGauche_ = VITESSE_MAX;
    break;
  }
}

void SuiveurLigne::suivreLigne(Moteur moteur)
{
  if (estEnMarche_)
  {
    switch (etat_)
    {
    case Etat::AVANCER_A_B:
    case Etat::AVANCER_B_C:
    case Etat::AVANCER_C_MUR:
    case Etat::AVANCER_MUR_C:
    case Etat::AVANCER_C_B:
    case Etat::AVANCER_H_C:
    case Etat::AVANCER_C_B_2:
    case Etat::AVANCER_B_G:
    case Etat::AVANCER_B_F:
    case Etat::AVANCER_F_POTEAU:
    case Etat::AVANCER_POTEAU_E:
    case Etat::TOURNER_E_GAUCHE:
    case Etat::AVANCER_E_D:
    case Etat::AVANCER_D_MUR:
    case Etat::RENCONTRER_MUR2:
    case Etat::AVANCER_MUR_D:
    case Etat::AVANCER_D_E:
    case Etat::AVANCER_E_MUR_VIRTUEL:
      miseAJourSenseurs();
      setVitesse();
      moteur.avancer(vitesseDroit_, vitesseGauche_);
      break;

    case Etat::TOURNER_SUR_LUI_MEME:
    case Etat::TOURNER_SUR_LUI_MEME_2:
    case Etat::TOURNER_C: // Possiblement ailleurs
      do
      {
        moteur.avancer(70, 0);
        miseAJourSenseurs();
      } while (senseurs_ != 0b00100);
      aligne_ = true;
      break;

    case Etat::TOURNER_B:
    case Etat::TOURNER_B_2:
      do
      {
        moteur.avancer(70, 0);
        miseAJourSenseurs();
      } while (senseurs_ != 0b00100);
      aligne_ = true;
      break;

    case Etat::TOURNER_D_DROIT:
    case Etat::TOURNER_E_DROIT:
      do
      {
        moteur.tournerDroit(VITESSE_MOY);
        miseAJourSenseurs();
      } while (senseurs_ != 0b00100);
      aligne_ = true;
      break;

    case Etat::TOURNER_D_GAUCHE:
      do
      {
        moteur.tournerGauche(VITESSE_MOY);
        miseAJourSenseurs();
      } while (senseurs_ != 0b00100);
      aligne_ = true;
      break;

    case Etat::AVANCER_G_H:
      senseurs_ = 0b00000;
      do
      {
        moteur.avancer(VITESSE_MOY, VITESSE_GAUCHE_OFFSET);
        miseAJourSenseurs();
      } while (senseurs_ == 0b00000);
      aligne_ = true;
      break;

    case Etat::AVANCER_JUSQUA_LIGNE:
      do
      {
        lcd.afficherNombreEnCm(5678);
        // avancer lentement
        moteur.avancer(VITESSE_MOY, VITESSE_GAUCHE_OFFSET);
        miseAJourSenseurs();
      } while (senseurs_ == 0b00000);
      ligneDetecte_ = true;
      break;

    case Etat::SE_REPLACER:
      do
      {
        moteur.avancer(50);

        miseAJourSenseurs();
      } while (senseurs_ > 0b01000);
      ligneDetecte_ = true;
      moteur.arreter();
      _delay_ms(1000);
      break;

    default:
      moteur.arreter();
      break;
    }
  }
}

void SuiveurLigne::setCoinDetecte(bool etat)
{
  coinDetecte_ = etat;
}

bool SuiveurLigne::getCoinDetecte()
{
  return coinDetecte_;
}

void SuiveurLigne::setAligne(bool etat)
{
  aligne_ = etat;
}

bool SuiveurLigne::getAligne()
{
  return aligne_;
}

void SuiveurLigne::setLigneDetecte(bool etat)
{
  ligneDetecte_ = etat;
}

bool SuiveurLigne::getLigneDetecte()
{
  return ligneDetecte_;
}
