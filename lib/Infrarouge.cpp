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
 * le fil bleu est relié au port 3 et le noir au port 4
*/

#include "Infrarouge.h"

Infrarouge::Infrarouge(uint8_t pinA)
{
    // Objet faisant la lecture
    lecteurCanPtr = new Can();

    // On définit le port qui sera utilisé
    pinA_ = pinA;

    voltage_ = 0;
}

Infrarouge::~Infrarouge() = default;

uint8_t Infrarouge::getVoltageMoyen()
{
    uint16_t somme = 0;

    for (uint8_t i = 0; i < 10; i++)
    {
        somme += getIntensiteLumineuse();
    }

    somme /= 10;

    voltage_ = static_cast<uint8_t>(somme);
    return voltage_;
}

uint8_t Infrarouge::getIntensiteLumineuse()
{
    return lecteurCanPtr->lecture(pinA_);
}
