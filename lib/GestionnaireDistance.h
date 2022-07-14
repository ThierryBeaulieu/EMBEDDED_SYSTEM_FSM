#ifndef GESTIONNAIREDISTANCE_H
#define GESTIONNAIREDISTANCE_H

#include "Infrarouge.h"
#include "Distance.h"

class GestionnaireDistance
{
public:
    GestionnaireDistance();
    ~GestionnaireDistance();

    uint8_t determineDistancePourLeMur();
    uint8_t determineDistancePourLePoteau();

    uint8_t getVoltage();


private:

    void calibrerDistance(); // distance entre le nez du robot et l'obstacle (cm)

    Infrarouge *infrarouge;
    uint16_t moyenneEchantillon_;
    uint8_t voltage_;
};

#endif /* GestionnaireDistance.h */
