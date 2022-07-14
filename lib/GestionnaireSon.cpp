/*
 * Travail : TP9
 * Auteurs : Karim El Hosni, Sara Beddouch, Thierry Beaulieu & Tuan Quoc Pham
 * Section # : 02
 * Équipe # : 2126
 *
 * Description: Ce programme implemente le gestionnaire de sonorite 
 */

#include "GestionnaireSon.h"

GestionnaireSon::GestionnaireSon(Sonorite son) : son(son) {}


void GestionnaireSon::distanceANote(uint8_t distance) {
    if (distance <= BORNE_INF) {
        son.jouerNote(NOTE_BORNE_INF);
    }
    else if (distance == BORNE_SUP) {
        son.jouerNote(NOTE_BORNE_SUP);
    }
    else if (distance > BORNE_INF && distance < BORNE_SUP) {
        son.jouerNote(interpollation(distance));
    }
    else if (distance > BORNE_SUP) {
        son.arreter();
    }
}

// extrapollation entre (12, 2000) et (24, 200)
uint8_t GestionnaireSon::interpollation(uint8_t distance) {
    return NOTE_BORNE_INF + ((distance - BORNE_INF) * RATIO_INTERPOLATION);
}
