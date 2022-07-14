/*
 * Travail : TP7
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham, 
 * Section # : 02
 * Équipe # : 2126
 * Description : Permet de faire la convertion d'un signal analogique entrant en
 * une variable de 8 bits.
 * Identifications matérielles :
 * La position du matériel est relative au port A choisit comme entrée.
 */

#ifndef CAN_H
#define CAN_H

#include <avr/io.h> 

class Can{
public:

   Can();
   ~Can();

   uint8_t lecture(uint8_t pos);
};

#endif /* CAN_H */
