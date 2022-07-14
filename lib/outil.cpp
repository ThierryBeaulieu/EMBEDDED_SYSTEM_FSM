#include "outil.h"
#include <avr/pgmspace.h>


float outil::ConvertirMetriqueEnImperial(float metrique)
{
    float nombreImperial = 0.0;

    metrique *= 0.393701; // convertion metrique à impérial

    int partieEntiere = static_cast<int>(metrique);

    float pariteAVirgule = metrique - partieEntiere;

    if (pariteAVirgule >= 0.0 && pariteAVirgule < 0.25)
    {
        pariteAVirgule = 0.0;
    }
    else if (pariteAVirgule >= 0.25 && pariteAVirgule < 0.75)
    {
        pariteAVirgule = 0.5;
    }
    else
    {
        pariteAVirgule = 0.0;
        partieEntiere += 1.0;
    }

    nombreImperial = nombreImperial + partieEntiere + pariteAVirgule;

    return nombreImperial;
}