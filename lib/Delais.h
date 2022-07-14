
/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu et Tuan Quoc Pham,
 * Section # : 02
 * Équipe # : 2126
 * Description : Permet de produire un délais à partir de la librarie de <util/delay.h>
 */

#ifndef DELAIS_H
#define DELAIS_H


#include <avr/io.h>
#include <util/delay.h>

class Delais{
public:
    Delais() = default;
    ~Delais() = default;

    void monDelais(uint16_t delaisMs);

};

#endif /* DELAIS_H */