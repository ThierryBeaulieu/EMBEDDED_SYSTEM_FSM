/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham, 
 * Section # : 02
 * Équipe # : 2126
 * Description : class Uart
 * Permet de faire une transmission de données de l'ATmega324 jusqu'à l'ordinateur
 * qui y ait connecté.
 * Identifications matérielles :
 * Aucun prérequis n'est nécessaire.
*/ 
 
#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

class Uart{
public:
   Uart();
   ~Uart();

   // Permet uniquement de transmettre un octet à la fois.
   void transmettreDonne(uint8_t donnee);

   void td(uint8_t donnee, uint8_t donne2, uint8_t donne3, uint8_t donne4, uint8_t donne5);

   void transmettreBinaire(uint8_t donnee);

   // Permet de faire l'affichage d'un uint8_t entre 1 et 255.
   void transmettreInt(uint8_t donnee);

   void transmettreBool(bool donnee);
   
   // Permet uniquement la réception un octet à la fois.
   uint8_t receptionDonne();

private:
   void initialisationUart();
};

#endif /* UART_H */
