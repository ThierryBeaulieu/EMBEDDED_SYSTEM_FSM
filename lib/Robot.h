/*
 * Travail : Projet finale
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme regroupe les composantes du robot au sein
 * d'une même classe
 */
#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <avr/io.h>
#include "Gestionnaire.h"
#include "GestionnaireDistance.h"
#include "Moteur.h"
#include "SuiveurLigne.h"
#include "Sonorite.h"
#include "GestionnaireSon.h"
#include "Lcd.h"
#include "Del.h"
#include "Minuterie1.h"
#include "outil.h"

class Robot
{
private:
    const uint8_t BORNE_NEGATIVE = 1;

public:
    Robot();
    void miseEnAttente();
    void activerSuiveurLigne(Etat etat);
    void afficherDistanceObstacle();
    Lcd *lcd;
    Moteur *moteur;
    Sonorite *son;
    Del *del;
    SuiveurLigne *suiveurLigne;
    GestionnaireDistance *gestionnaireDistance;
    GestionnaireSon *gestionnaireSon;
    Minuterie1 *minuterie;
    bool estAfficheEnCentimetres;
    bool sonActive;
    uint8_t distanceObstacleEnCm;
};
#endif // Robot_H