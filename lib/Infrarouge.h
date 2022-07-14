/*
 * Auteur: Thierry Beaulieu
 * 
 * Description : Classe Infrarouge
 * Le constructeur initialise le convertisseur.
 * Un objet de type Can permet de convertir le signal digital
 * entrant en un uint8_t.
 * 
 * Identifications matérielles : 
 * Le câble formé de la paire rouge (+) et noir (-) est reliée au VCC et GND du port D:
 * le fil rouge est relié au VCC et le noir au GND
 * Le câble formé de la paire bleu (+) et noir (-) est reliée aux ports 3 (-) et 4 (+) du port A:
 * le fil bleu est relié au port 3 et le noir au port 4. 
*/

#ifndef INFRAROUGE_H
#define INFRAROUGE_H

#include <avr/io.h>
#include "Can.h"
#include "Gestionnaire.h"
#include "Uart.h"
#include "Delais.h"

class Infrarouge
{
public:
    Infrarouge(uint8_t pinA = 6); // pin de A (0-7)
    ~Infrarouge();

    uint8_t getIntensiteLumineuse();

private:
    uint8_t getVoltageMoyen();
private:
    uint8_t voltage_;
    uint8_t pinA_;
private:
    Can *lecteurCanPtr;
};

#endif /* Infrarouge.h */
