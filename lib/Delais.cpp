#include <Delais.h>


/**
 * Permet de faire perdre du temps en fonction d'un nombre
 * de millisecondes.

 * @param  delaisMs: Le nombre de milliseconde d'attente demandé par l'utilisateur.
 * @return void
*/
void Delais::monDelais(uint16_t delaisMs){

    delaisMs /= 5;
    for(uint16_t i = 0; i < delaisMs; i++)
        _delay_ms(5);

}