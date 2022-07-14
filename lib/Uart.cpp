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
#include "Uart.h"

/**
 * Constructeur. Fait l'appel d'une méthode privé qui fera l'initialisation des registres.s
 *
 * @param None
 * @return void
 */
Uart::Uart()
{
    initialisationUart();
}

/**
 * Destruction qui ne fait rien.
 *
 * @param None
 * @return void
 */
Uart::~Uart() {}

/**
 * Initialise les registres nécessaire pour faire la transmission d'information.
 *
 * @param None
 * @return void
 */
void Uart::initialisationUart(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux
    // bauds ce sont des bit par seconde.
    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;
    UBRR0L = 0xCF;

    // Le registre UCSR0A n'est pas vraiment utilise, puisque ces r
    // UCSR0A = 0;

    // On ajoute UCSZ02 pour définir que les caractères d'entrées soient définient sur 8 bits.
    // Pour être définit sur 8 bits, il faut que les registres UCSZ02, UCSZ01 et UCSZ00 soient égales
    // à 0, 1 et 1. Par contre, UCSZ02 se trouve dans UCSR0B alors que UCSZ01 et UCSZ00 se trouvent dans
    // le registre UCSR0C. On active la réception (RX) et la transimission (TX) de données
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (0 << UCSZ02);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

/**
 * Fait la transmission d'un uint8_t à un port en série.
 *
 * @param donnee Donnee à transmettre aux port en série
 * @return None rien à renvoyer
 */
void Uart::transmettreDonne(uint8_t donnee)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = donnee;
}


void Uart::td(uint8_t donnee, uint8_t donne2, uint8_t donne3, uint8_t donne4, uint8_t donne5)
{
    transmettreDonne(donnee);
    transmettreDonne(donne2);
    transmettreDonne(donne3);
    transmettreDonne(donne4);
    transmettreDonne(donne5);
}

/**
 * Fait la réception d'un uint8_t et le retourne.
 *
 * @return une donnée uint8_t sur 1 octet
 */
uint8_t Uart::receptionDonne()
{ /* Attendre que la donnée soi reçue */
    while (!(UCSR0A & (1 << RXC0)))
        ; /* Retourne la donnée */
    return UDR0;
}

void Uart::transmettreBinaire(uint8_t donnee)
{
    for (int i = 7; i >= 0; --i)
    {
        transmettreDonne((donnee & (1 << i)) ? '1' : '0');
    }
    transmettreDonne('\n');
}

void Uart::transmettreInt(uint8_t donnee)
{
    uint8_t i = 7;
    char nombre[8] = "";

    if (donnee == 0)
    {
        transmettreDonne('0');
    }

    uint8_t tmp = 0;
    while (donnee > 0)
    {
        tmp = donnee % 10;
        nombre[i] = 48 + tmp;
        donnee /= 10;
        i--;
    }

    // Il faut envoyer les données, mais dans
    // le sens inverse.
    for (uint8_t i = 0; i < 8; i++)
    {
        transmettreDonne(nombre[i]);
    }

    transmettreDonne('\n');
}

void Uart::transmettreBool(bool donnee)
{
    if (donnee)
    {
        transmettreInt(1);
    }
    else
    {
        transmettreInt(0);
    }
}