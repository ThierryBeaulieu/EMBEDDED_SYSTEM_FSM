/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Ce programme implemente des methodes qui aide dans l'eclairage de la Del bicolore
 */

#include <avr/io.h>
#include <util/delay.h>


const uint8_t VERT = 0b10;
const uint8_t ROUGE = 0b01;
const uint8_t ETEINT = 0b00;
const uint8_t ATTENTE_DEL = 50;
const uint8_t ATTENTE_TOTAL = 100;

class Del
{

public:
    // constructeur
    Del();

    // destructeur
    ~Del();

    // methode pour allumer la del en rouge
    void allumerDelRouge(volatile uint8_t &, uint8_t);

    // methode pour allumer la del en vert
    void allumerDelVert(volatile uint8_t &, uint8_t);

    // methode pour allumer la del en ambre.
    void allumerDelAmbre(volatile uint8_t &, uint8_t, uint8_t);

    // methode pour eteindre la del
    void eteindreDel(volatile uint8_t &, uint8_t);
};
