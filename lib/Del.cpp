/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description :
 * Cette classe a pour role de faciliter l'eclairage de la del,
 * en offrant le choix a l'utilisateur de choisir le port,
 * les broches convenable et 3 possiblites d'eclairage avec une
 * possiblitie d'eteindre la del
 */
#include "Del.h"


uint8_t ajuster(uint8_t numero)
{
    return numero - 2;
}

/**
 * Constructeur par defaut.

 * @param  aucun parametre
 * @return void
*/
Del::Del() = default;

/**
 * Destructeur par defaut.

 * @param  aucun parametre
 * @return void
*/
Del::~Del() = default;

/**
 * methode qui allume la del en rouge

 * @param  port represente le port qu'on utilise.
  * @param  borneNegative  represente la broche relier au pole negative de la del.
 * @return void
*/
void Del::allumerDelRouge(volatile uint8_t &port, uint8_t borneNegative)
{
    port = ROUGE << ajuster(borneNegative);
}

/**
 * methode qui allume la del en vert.

 * @param  port represente le port qu'on utilise.
 * @param  borneNegative  represente la broche relier au pole negative de la del.
 * @return void
*/
void Del::allumerDelVert(volatile uint8_t &port, uint8_t borneNegative)
{
    port = VERT << ajuster(borneNegative);
}

/**
 * methode qui allume la del en ambre.

 * @param  port represente le port qu'on utilise.
 * @param  borneNegative  represente la broche relier au pole negative de la del.
 * @param  tempsEnSeconde represente le temps necessaire en seconde  pour  allumer la del en ambre.
 * @return void
*/

void Del::allumerDelAmbre(volatile uint8_t &port, uint8_t borneNegative, uint8_t tempsEnSeconde)
{
    uint8_t compteurBoucle = (tempsEnSeconde * 1000) / ATTENTE_TOTAL; // temps en ms diviser par le temps necessaire de faire une boucle.
    for (uint8_t i = 0; i < compteurBoucle; i++)
    {
        port = VERT << ajuster(borneNegative);
        _delay_ms(ATTENTE_DEL);
        port = ROUGE << ajuster(borneNegative);
        _delay_ms(ATTENTE_DEL);
    }
}

/**
 * methode qui fait eteindre la Del.

 * @param  port represente le port qu'on utilise.
 * @param  borneNegative  represente la broche relier au pole negative de la del.
 * @return void
*/
void Del::eteindreDel(volatile uint8_t &port, uint8_t borneNegative)
{
    port = ETEINT << ajuster(borneNegative);
}