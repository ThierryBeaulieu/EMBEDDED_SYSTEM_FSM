/*
 * Travail : Projet final
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme fait avancer un robot selon un parcours pré-planifé.
 *
 * Identifications matérielles :
 *
 * Cavalier sur IntEN
 *
 *
 * DEL libre (port +, cable +), (port -, cable -)
 * PORT D (port 1, cable +), (port 2, cable -)
 *
 * Pour le moteur :
 *  B3 <=> D moteur#1
 *  B4 <=> E moteur#1
 *  B5 <=> E moteur#2
 *  B6 <=> D moteur#2
 *
 * Pour la sonorite :
 *  D7  <=> fil rouge
 *  D8 <=> fil noir
 *
 * Pour le LCD :
 *  Utiliser tout le portC au complet et s'assurer que :
 *  le fil rouge est sur VCC et et le fil noir sur GND
 *
 * Pour le bouton blanc :
 *  VCC et GND du portD
 *  Le circuit du breadboard où est situé le bouton blanc
 *  est le même que celui du problème 1 du TP6
 *
 * Pour le suiveur de lignes :
 *  Ports A1 à A6 et le VCC et GND du même port
 *
 * Pour le capteur de distances :
 *  Port A7
 *
 */


/*
 * Voici le diagramme d'état du système embarqué
 +------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|     État   présent     | Bouton Interupt | Suiveur de   ligne | Capteur de   distance | Minuterie |      État suivant      | Sortie |
+========================+=================+====================+=======================+===========+========================+========+
|          INIT          |        0        |          -         |           -           |     -     |   ATTENTE_INTERRUPT_1  |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|   ATTENTE_INTERRUPT_1  |        1        |          -         |           -           |     -     |       AVANCER_A_B      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_A_B      |        -        |          1         |           -           |     -     |       AVANCER_B_C      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_B_C      |        -        |          1         |           -           |     -     |      AVANCER_C_MUR     |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|      AVANCER_C_MUR     |        -        |          -         |           1           |     -     |      RECONTRER_MUR     |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|      RECONTRER_MUR     |        0        |          -         |           -           |     -     |   ATTENTE_INTERRUPT_2  |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|   ATTENTE_INTERRUPT_2  |        1        |          -         |           -           |     1     |  TOURNER_SUR_LUI_MEME  |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|  TOURNER_SUR_LUI_MEME  |        -        |          1         |           -           |     -     |      AVANCER_MUR_C     |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|      AVANCER_MUR_C     |        -        |          1         |           -           |     -     |       AVANCER_C_B      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_C_B      |        -        |          1         |           -           |     -     |        TOURNER_B       |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|        TOURNER_B       |        -        |          1         |           -           |     -     |       AVANCER_B_G      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_B_G      |        -        |          -         |           -           |     1     |        TOURNER_G       |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|        TOURNER_G       |        -        |          -         |           -           |     1     |       AVANCER_G_H      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_G_H      |        -        |          -         |           -           |     1     |       AVANCER_H_C      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_H_C      |        -        |          1         |           -           |     -     |        TOURNER_C       |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|        TOURNER_C       |        -        |          1         |           -           |     -     |      AVANCER_C_B_2     |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|      AVANCER_C_B_2     |        -        |          1         |           -           |     -     |       TOURNER_B_2      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       TOURNER_B_2      |        -        |          1         |           -           |     -     |       AVANCER_B_F      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_B_F      |        -        |          1         |           -           |     -     |        TOURNER_F       |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|        TOURNER_F       |        -        |          1         |           -           |     -     |    AVANCER_F_POTEAU    |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|    AVANCER_F_POTEAU    |        -        |          -         |           1           |     -     |    RENCONTRER_POTEAU   |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|    RENCONTRER_POTEAU   |        0        |          -         |           -           |     -     |   ATTENTE_INTERRUPT_3  |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|   ATTENTE_INTERRUPT_3  |        1        |          -         |           -           |     -     |    CONTOURNER_POTEAU   |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|    CONTOURNER_POTEAU   |        -        |          -         |           -           |     1     |    AVANCER_POTEAU_E    |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|    AVANCER_POTEAU_E    |        -        |          1         |           -           |     -     |    TOURNER_E_GAUCHE    |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|    TOURNER_E_GAUCHE    |        -        |          1         |           -           |     -     |       AVANCER_E_D      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_E_D      |        -        |          1         |           -           |     -     |    TOURNER_D_GAUCHE    |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|    TOURNER_D_GAUCHE    |        -        |          1         |           -           |     -     |      AVANCER_D_MUR     |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|      AVANCER_D_MUR     |        -        |          -         |           1           |     -     |   ATTENTE_INTERRUPT_4  |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|   ATTENTE_INTERRUPT_4  |        1        |          -         |           -           |     -     | TOURNER_SUR_LUI_MEME_2 |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
| TOURNER_SUR_LUI_MEME_2 |        -        |          1         |           -           |     -     |      AVANCER_MUR_D     |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|      AVANCER_MUR_D     |        -        |          1         |           -           |     -     |     TOURNER_D_DROIT    |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|     TOURNER_D_DROIT    |        -        |          1         |           -           |     -     |       AVANCER_D_E      |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|       AVANCER_D_E      |        -        |          1         |           -           |     -     |     TOURNER_E_DROIT    |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|     TOURNER_E_DROIT    |        -        |          1         |           -           |     -     |  AVANCER_E_MUR_VIRTUEL |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|  AVANCER_E_MUR_VIRTUEL |        -        |          -         |           -           |     1     |           FIN          |    0   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
|           FIN          |        -        |          -         |           -           |     -     |            -           |    1   |
+------------------------+-----------------+--------------------+-----------------------+-----------+------------------------+--------+
*/



// Voici la version final! Enjoy!



#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

#include <SuiveurLigne.h>
#include <Robot.h>
#include <Uart.h>

const int VITESSE_MOY = 50;
const uint8_t TOUTE_SORTIE = 0xff;
const uint8_t TOUTE_ENTREE = 0x00; // seuls PD2 et PD3 sont en mode entrée
const uint8_t DELAIS_ANTIREBOND = 10;
const uint8_t BORNE_NEGATIVE = 1;
const uint8_t NOMBRE_FOIS_MISE_A_JOUR_FREQUENCE = 30;
const uint8_t DISTANCE_BC_EN_CM = 38;
const float DISTANCE_ATTENTE_MUR2_CM = 1.27;
constexpr float DEPASSEMENT_TOURNANT = 0.5;
const uint8_t DISTANCE_NOISE = 0;
const uint8_t DISTANCE_A_ATTEINDRE = 30 + DISTANCE_NOISE;
const uint8_t DISTANCE_A_ATTEINDRE_SECOND_MUR = 10;

const uint16_t DELAIS_MISE_ATTENTE = 2000;
const uint16_t NOMBRE_SECONDES_MINUTERIE_BG = 1;
const float NOMBRE_MILLI_SECONDES_MINUTERIE = 0.001;
const float DELAIS_INTERVAL_B_G = 4.36;

volatile bool gEstInterruptAppuyee = false;
volatile bool gEstBoutonBlancAppuyee = false;
volatile bool gMinuterieExpiree = false;
volatile bool estAffichageAJour = true;

bool estEnAttente = false;
volatile float compteurSecondes = 0;
volatile float compteurSingulier = 0;
float vitesseRobot = 0;
float nombreSecondes_Point_Obstacle = 0;
float distanceRobotMur2 = 0;
float tempsRobotMur2 = 0;
float compteurChrono = 0;

void initialisationInterruptions()
{

    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes sur le port 0 et 1
    EIMSK |= (1 << INT0) | (1 << INT1);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00) | (1 << ISC10);

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

// Minuterie
ISR(TIMER1_COMPA_vect)
{
    gMinuterieExpiree = true;
    compteurSecondes += 0.001;
    compteurSingulier += 0.5;
}

// Interupt
ISR(INT0_vect)
{
    _delay_ms(DELAIS_ANTIREBOND);
    gEstInterruptAppuyee = true;
    EIFR |= (1 << INTF0);
}

// Bouton blanc
ISR(INT1_vect)
{
    _delay_ms(DELAIS_ANTIREBOND);
    gEstBoutonBlancAppuyee = !gEstBoutonBlancAppuyee;
    if (gEstBoutonBlancAppuyee)
    {
        estAffichageAJour = false;
    }
    EIFR |= (1 << INTF1);
}

void boutonInterruptAppuye(Robot &robot)
{
    estEnAttente = false;
    robot.lcd->effacer();
    robot.del->allumerDelVert(PORTD, BORNE_NEGATIVE);
    gEstInterruptAppuyee = false;
    _delay_ms(DELAIS_MISE_ATTENTE);
}

void miseEnAttente(Robot &robot)
{
    estEnAttente = true;
    robot.miseEnAttente();
}


bool peutJouerSon(Etat &etat)
{
    return !estEnAttente &&
           (etat == Etat::AVANCER_C_MUR ||
            etat == Etat::TOURNER_SUR_LUI_MEME ||
            etat == Etat::AVANCER_F_POTEAU ||
            etat == Etat::AVANCER_D_MUR);
}

int main()
{
    Uart uart;
    Robot robot;

    initialisationInterruptions();

    Etat etat = Etat::INIT;
    
    while (true)
    {
        if (estEnAttente && gEstBoutonBlancAppuyee && !estAffichageAJour)
        {
            robot.estAfficheEnCentimetres = !robot.estAfficheEnCentimetres;
            robot.afficherDistanceObstacle();
            estAffichageAJour = true;
        }

        // Mise à jour de la fréquence
        if (peutJouerSon(etat))
        {
            robot.gestionnaireSon->distanceANote(robot.gestionnaireDistance->determineDistancePourLeMur());
        }
        else
        {
            robot.gestionnaireSon->son.arreter();
        }

        switch (etat)
        {
        case Etat::INIT:
            robot.lcd->afficherNombreEnCm(0);
            miseEnAttente(robot);
            etat = Etat::ATTENTE_INTERRUPT_1;
            break;

        case Etat::ATTENTE_INTERRUPT_1:
            robot.lcd->afficherNombreEnCm(0);
            if (gEstInterruptAppuyee)
            {
                boutonInterruptAppuye(robot);
                etat = Etat::AVANCER_A_B;
            }
            break;

        case Etat::AVANCER_A_B:
            robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                /*
                gMinuterieExpiree = false;
                robot.minuterie->partirMinuterie(1);
                do
                {
                    robot.activerSuiveurLigne(etat);
                } while (!gMinuterieExpiree);
                */
                compteurSecondes = 0;
                robot.minuterie->partirMinuterie(NOMBRE_MILLI_SECONDES_MINUTERIE);
                etat = Etat::AVANCER_B_C;
            }
            break;

        case Etat::AVANCER_B_C:
            robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                vitesseRobot = DISTANCE_BC_EN_CM / compteurSecondes;
                gMinuterieExpiree = false;
                robot.minuterie->partirMinuterie(1);
                do
                {
                    robot.activerSuiveurLigne(etat);
                } while (!gMinuterieExpiree);
                etat = Etat::AVANCER_C_MUR;
            }
            break;

        case Etat::AVANCER_C_MUR:
            robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.gestionnaireDistance->determineDistancePourLeMur() <= DISTANCE_A_ATTEINDRE)
            {
                robot.distanceObstacleEnCm = static_cast<uint8_t>(vitesseRobot * (compteurSecondes + 2)) + DISTANCE_A_ATTEINDRE;
                etat = Etat::RENCONTRER_MUR;
                gEstInterruptAppuyee = false;
            }
            break;

        case Etat::RENCONTRER_MUR:
            robot.lcd->afficherNombreEnCm(0);
            miseEnAttente(robot);
            etat = Etat::ATTENTE_INTERRUPT_2;
            break;

        case Etat::ATTENTE_INTERRUPT_2:
            // robot.lcd->afficherNombreEnCm(0);
            if (gEstInterruptAppuyee)
            {
                boutonInterruptAppuye(robot);
                etat = Etat::TOURNER_SUR_LUI_MEME;
                robot.moteur->tournerSurLuiMeme();
            }
            break;

        case Etat::TOURNER_SUR_LUI_MEME:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_MUR_C;
            }
            break;

        case Etat::AVANCER_MUR_C:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                gMinuterieExpiree = false;
                robot.minuterie->partirMinuterie(1);
                do
                {
                    
                    robot.activerSuiveurLigne(etat);
                } while (!gMinuterieExpiree);
                
                etat = Etat::AVANCER_C_B;
            }
            break;

        case Etat::AVANCER_C_B:
            // robot.lcd->afficherNombreEnCm(0);
            
            robot.activerSuiveurLigne(etat);

            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                gMinuterieExpiree = false;
                robot.minuterie->partirMinuterie(DEPASSEMENT_TOURNANT);
                do
                {
                    robot.activerSuiveurLigne(etat);
                } while (!gMinuterieExpiree);
                robot.suiveurLigne->activerSL(false);
                robot.moteur->tourner90Gauche();
                etat = Etat::TOURNER_B;
            }
            break;

        case Etat::TOURNER_B:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);

            if (robot.suiveurLigne->getAligne() == true)
            {

                etat = Etat::AVANCER_B_G;
            }
            break;

        case Etat::AVANCER_B_G:

            // robot.lcd->afficherNombreEnCm(0);
            robot.minuterie->partirMinuterie(DELAIS_INTERVAL_B_G);
            gMinuterieExpiree = false;
            do
            {
                robot.activerSuiveurLigne(etat);
            } while (!gMinuterieExpiree);
            etat = Etat::TOURNER_G;
            break;

        case Etat::TOURNER_G:
            // robot.lcd->afficherNombreEnCm(0);
            robot.moteur->tourner145Degrees();
            etat = Etat::AVANCER_G_H;
            break;

        case Etat::AVANCER_G_H:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_H_C;
            }
            break;

        case Etat::AVANCER_H_C:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                etat = Etat::TOURNER_C;
                robot.moteur->tourner35Degrees();
            }
            break;

        case Etat::TOURNER_C:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_C_B_2;
            }
            break;

        case Etat::AVANCER_C_B_2:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                gMinuterieExpiree = false;
                robot.minuterie->partirMinuterie(DEPASSEMENT_TOURNANT);
                do
                {
                    robot.activerSuiveurLigne(etat);
                } while (!gMinuterieExpiree);
                robot.suiveurLigne->activerSL(false);
                robot.moteur->tourner90Gauche();
                etat = Etat::TOURNER_B_2;
            }
            break;

        case Etat::TOURNER_B_2:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_B_F;
            }
            break;

        case Etat::AVANCER_B_F:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                /*
                gMinuterieExpiree = false;
                robot.minuterie->partirMinuterie(1);
                do
                {
                    robot.activerSuiveurLigne(etat);
                } while (!gMinuterieExpiree);
                */
                compteurSecondes = 0;
                robot.minuterie->partirMinuterie(NOMBRE_MILLI_SECONDES_MINUTERIE);
                etat = Etat::AVANCER_F_POTEAU;
            }
            break;

        case Etat::AVANCER_F_POTEAU:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.gestionnaireDistance->determineDistancePourLePoteau() <= DISTANCE_A_ATTEINDRE)
            {
                robot.distanceObstacleEnCm = static_cast<uint8_t>(vitesseRobot * compteurSecondes) + DISTANCE_A_ATTEINDRE;
                etat = Etat::RENCONTRER_POTEAU;
                gEstInterruptAppuyee = false;
            }
            break;

        case Etat::RENCONTRER_POTEAU:
            // robot.lcd->afficherNombreEnCm(0);
            miseEnAttente(robot);
            etat = Etat::ATTENTE_INTERRUPT_3;
            break;

        case Etat::ATTENTE_INTERRUPT_3:
            // robot.lcd->afficherNombreEnCm(0);
            if (gEstInterruptAppuyee)
            {
                boutonInterruptAppuye(robot);
                etat = Etat::CONTOURNER_POTEAU;
            }
            break;

        case Etat::CONTOURNER_POTEAU:
            // robot.lcd->afficherNombreEnCm(0);
            robot.suiveurLigne->activerSL(false);

            robot.moteur->tourner45Degrees();
            robot.minuterie->partirMinuterie(3.25);
            gMinuterieExpiree = false;
            do
            {
                robot.moteur->avancer(80);
            } while (!gMinuterieExpiree);
            robot.suiveurLigne->activerSL(false);

            robot.moteur->tourner90Poteau();
            etat = Etat::AVANCER_JUSQUA_LIGNE;
            break;

        case Etat::AVANCER_JUSQUA_LIGNE:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getLigneDetecte() == true)
            {
                robot.moteur->arreter();
                etat = Etat::SE_REPLACER;
            }

            break;

        case Etat::SE_REPLACER:
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getLigneDetecte() == true)
            {
                etat = Etat::AVANCER_POTEAU_E;
            }

            break;

        case Etat::AVANCER_POTEAU_E:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);

            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                robot.moteur->arreter();
                etat = Etat::TOURNER_E_GAUCHE;
            }
            break;

        case Etat::TOURNER_E_GAUCHE:
            // robot.lcd->afficherNombreEnCm(0);
            gMinuterieExpiree = false;
            robot.minuterie->partirMinuterie(DEPASSEMENT_TOURNANT);
            do
            {
                robot.activerSuiveurLigne(etat);
            } while (!gMinuterieExpiree);
            robot.suiveurLigne->activerSL(false);
            robot.moteur->tourner90Gauche();
            etat = Etat::AVANCER_E_D;
            break;

        case Etat::AVANCER_E_D:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                etat = Etat::TOURNER_D_GAUCHE;
            }
            break;

        case Etat::TOURNER_D_GAUCHE:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_D_MUR;
            }
            break;

        case Etat::AVANCER_D_MUR:
            // robot.lcd->afficherNombreEnCm(0);

            robot.activerSuiveurLigne(etat);

            // Avancera jusqu'au mur à une distance de 8 cm.
            if (robot.gestionnaireDistance->determineDistancePourLeMur() <= DISTANCE_A_ATTEINDRE_SECOND_MUR)
            {
                etat = Etat::RENCONTRER_MUR2;
                gEstInterruptAppuyee = false;
            }

            break;

        case Etat::RENCONTRER_MUR2:
            // robot.lcd->afficherNombreEnCm(0);
            robot.moteur->arreter();

            // Avancera jusqu'à une distance de 0.5 pouce.
            gMinuterieExpiree = false;
            robot.suiveurLigne->activerSL(false);
            robot.minuterie->partirMinuterie(0.6); // 0.5 à 1.6 A
            gMinuterieExpiree = false;
            do
            {
                robot.moteur->avancer(60); // Trouver le juste milieu de la bonne puissance.
            } while (!gMinuterieExpiree);
            // robot.suiveurLigne->activerSL(false);

            // robot.lcd->afficherNombreEnCm(0);
            miseEnAttente(robot);
            etat = Etat::ATTENTE_INTERRUPT_4;
            break;

        case Etat::ATTENTE_INTERRUPT_4:
            // robot.lcd->afficherNombreEnCm(31);
            if (gEstInterruptAppuyee)
            {
                boutonInterruptAppuye(robot);
                etat = Etat::TOURNER_SUR_LUI_MEME_2;
                robot.moteur->tournerSurLuiMeme();
            }
            break;

        case Etat::TOURNER_SUR_LUI_MEME_2:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_MUR_D;
            }
            break;

        case Etat::AVANCER_MUR_D:
            // robot.lcd->afficherNombreEnCm(0);
            // TODO: Démarer minuterie
            compteurSecondes = 0;
            compteurSingulier = 0;
            robot.minuterie->partirChrono();
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                etat = Etat::TOURNER_D_DROIT;
            }
            break;

        case Etat::TOURNER_D_DROIT:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_D_E;
            }

            break;

        case Etat::AVANCER_D_E:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getCoinDetecte() == true)
            {
                etat = Etat::TOURNER_E_DROIT;
            }
            break;

        case Etat::TOURNER_E_DROIT:
            // robot.lcd->afficherNombreEnCm(0);
            robot.activerSuiveurLigne(etat);
            if (robot.suiveurLigne->getAligne() == true)
            {
                etat = Etat::AVANCER_E_MUR_VIRTUEL;
            }

            break;

        case Etat::AVANCER_E_MUR_VIRTUEL:
            // robot.lcd->afficherNombreEnCm(compteurChrono);
            // Avancer pendant le temps qu'on a définit dans le chrono. // compteurChrono
            robot.minuterie->partirMinuterie(compteurChrono-4); // 4 à 1.4V
            gMinuterieExpiree = false;
            do
            {
                robot.lcd->afficherNombreEnCm(68);
                robot.activerSuiveurLigne(etat);
            } while (!gMinuterieExpiree);

            etat = Etat::FIN;
            break;
            
        case Etat::FIN:
            robot.del->eteindreDel(PORTD, BORNE_NEGATIVE);
            robot.suiveurLigne->activerSL(false);
            robot.gestionnaireSon->son.arreter();
            robot.moteur->arreter();
            break;
        }
    }
}
