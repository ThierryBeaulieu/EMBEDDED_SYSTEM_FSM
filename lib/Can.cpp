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

#include "Can.h"

/**
 * Initialisation du convertisseur
 *
 * @param None
 * @return void
 */
Can::Can(){
   // ADC mux : reference analogique externe
   //           ajuste a droite
   ADMUX  = ( 0 << REFS1 ) | ( 0 << REFS0 ) | ( 0 << ADLAR ) | ( 0 << MUX4 ) |
            ( 0 << MUX3 ) | ( 0 << MUX2 ) | ( 0 << MUX1) | ( 0 << MUX0 ) ;

   // ADC Status and Control Register A : 
   //  Active le convertisseur mais sans demarrer de conversion pour l'instant.
   //  Pas de declanchement automatique et aucune interruption suivant
   //  la fin d'une convertion. Division de l'horloge par 64 (il faudra
   //  donc 13 cycles du convertisseur * 64 pour terminer une conversion
   //  soit 832 cycles d'horloge soit 104 micro-secondes
   ADCSRA = ( 1 << ADEN ) | ( 0 << ADSC )  | ( 0 << ADATE ) | ( 0 << ADIF ) |
            ( 0 << ADIE ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 0 << ADPS0 ) ;
}

/**
 * Destruction du convertisseur: Arrêt de la transmission de données.
 *
 * @param None
 * @return void
 */
Can::~Can(){
   // rendre le convertisseur inactif.
   ADCSRA = 0 << ADEN ;
}


/**
 * Renvoie une convertion d'un signal digital en un nombre codé sur 8 bits.
 *
 * @param pos     position de la pin du port A qui reçoit le signal.
 * @return void
 */
uint8_t
Can::lecture( uint8_t pos){
   uint16_t adcVal;

   // Garder les bits de ADMUX intacts, sauf les bit permettant 
   // la selection de l'entree
   ADMUX  &=  ~(( 1 << MUX4 ) | ( 1 << MUX3 ) | 
                ( 1 << MUX2 ) | ( 1 << MUX1)  | ( 1 << MUX0 ));

   // selectionner l'entree voulue
   ADMUX |= ((pos & 0x07) << MUX0) ;

   // demarrer la conversion
   ADCSRA |= ( 1 << ADSC );

   // Attendre la fin de la conversion soit 13 cycles du convertisseur.
   while( ! (ADCSRA & ( 1 << ADIF ) ) );

   // important: remettre le bit d'indication de fin de cycle a zero 
   // pour la prochaine conversion ce qui se fait en l'ajustant a un.
   ADCSRA |= (1 << ADIF);

   // Aller chercher le resultat sur 16 bits.
   adcVal =   ADCL ;
   adcVal +=  ADCH << 8;

   // Convertie les 10 bits utiles en un integer de 8 bits.
   uint8_t adcValConverti = adcVal >> 2;

   // resultat des 8 bits.
   return adcValConverti;
}

