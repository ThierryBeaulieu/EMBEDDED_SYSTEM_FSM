/*
 * Travail : Projet finale
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme est un controlleur qui gère les composantes du robot
 */
#include "Robot.h"
Robot::Robot()
{
    DDRD = (1 << DDD0) | (1 << DDD1) | (1 << DDD6) | (1 << DDD7);
    del = new Del();
    lcd = new Lcd();
    suiveurLigne = new SuiveurLigne();
    moteur = new Moteur(PrescaleurTimer0::T0_P8);
    gestionnaireDistance = new GestionnaireDistance();
    gestionnaireSon = new GestionnaireSon(Sonorite());
    minuterie = new Minuterie1();
    estAfficheEnCentimetres = false;
    sonActive = false;
    distanceObstacleEnCm = 0;
}

void Robot::miseEnAttente()
{
    afficherDistanceObstacle();
    suiveurLigne->activerSL(false);
    gestionnaireSon->son.arreter();
    moteur->arreter();
    del->allumerDelRouge(PORTD, BORNE_NEGATIVE);
}

void Robot::activerSuiveurLigne(Etat etat)
{
    suiveurLigne->setEtatGlobal(etat);
    suiveurLigne->setCoinDetecte(false);
    suiveurLigne->setAligne(false);
    suiveurLigne->setLigneDetecte(false);
    suiveurLigne->activerSL(true);
    suiveurLigne->suivreLigne(*moteur);
}

void Robot::afficherDistanceObstacle()
{
    if (estAfficheEnCentimetres)
    {
        lcd->afficherNombreEnCm(distanceObstacleEnCm);
    }
    else
    {
        lcd->afficherNombreEnPo(outil::ConvertirMetriqueEnImperial(distanceObstacleEnCm));
    }
}