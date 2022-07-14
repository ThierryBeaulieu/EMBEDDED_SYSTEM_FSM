#include "GestionnaireDistance.h"

const int8_t SIZE_ECHANTILLON = 18;

GestionnaireDistance::GestionnaireDistance()
{
    infrarouge = new Infrarouge();
    voltage_ = 0;
    moyenneEchantillon_ = 0;
}

GestionnaireDistance::~GestionnaireDistance() = default;

uint8_t GestionnaireDistance::getVoltage()
{

    calibrerDistance();

    return voltage_;
}

void GestionnaireDistance::calibrerDistance()
{
    uint8_t echantillon[SIZE_ECHANTILLON];

    for (uint8_t i = 0; i < SIZE_ECHANTILLON; i++)
    {
        echantillon[i] = infrarouge->getIntensiteLumineuse();
    }

    uint8_t min = echantillon[0];
    uint8_t max = echantillon[0];

    for (uint8_t i = 0; i < SIZE_ECHANTILLON; i++)
    {
        if (echantillon[i] < min)
        {
            min = echantillon[i];
        }

        if (echantillon[i] > max)
        {
            max = echantillon[i];
        }
    }

    moyenneEchantillon_ = 0;

    for (uint8_t i = 0; i < SIZE_ECHANTILLON; i++)
    {
        moyenneEchantillon_ += echantillon[i];
    }
    moyenneEchantillon_ -= min;
    moyenneEchantillon_ -= max;

    voltage_ = moyenneEchantillon_ >> 4;
}

uint8_t GestionnaireDistance::determineDistancePourLeMur()
{
    calibrerDistance();

    if (voltage_ >= 156)
    {
        return Distance::DE_5_CM;
    }
    if (voltage_ >= 145)
    {
        return Distance::DE_6_CM;
    }
    if (voltage_ >= 130)
    {
        return Distance::DE_7_CM;
    }
    if (voltage_ >= 119)
    {
        return Distance::DE_8_CM;
    }
    if (voltage_ >= 107)
    {
        return Distance::DE_9_CM;
    }
    if (voltage_ >= 96)
    {
        return Distance::DE_10_CM;
    }
    if (voltage_ >= 91)
    {
        return Distance::DE_11_CM;
    }
    if (voltage_ >= 85)
    {
        return Distance::DE_12_CM;
    }
    if (voltage_ >= 82)
    {
        return Distance::DE_13_CM;
    }
    if (voltage_ >= 81)
    {
        return Distance::DE_14_CM;
    }
    if (voltage_ >= 79)
    {
        return Distance::DE_15_CM;
    }
    if (voltage_ >= 78)
    {
        return Distance::DE_16_CM;
    }
    if (voltage_ >= 75)
    {
        return Distance::DE_17_CM;
    }
    if (voltage_ >= 72)
    {
        return Distance::DE_19_CM;
    }
    if (voltage_ >= 69)
    {
        return Distance::DE_20_CM;
    }
    if (voltage_ >= 67)
    {
        return Distance::DE_23_CM;
    }
    if (voltage_ >= 66)
    {
        return Distance::DE_24_CM;
    }
    if (voltage_ >= 63)
    {
        return Distance::DE_25_CM;
    }
    if (voltage_ >= 61)
    {
        return Distance::DE_26_CM;
    }
    if (voltage_ >= 60)
    {
        return Distance::DE_27_CM;
    }
    if (voltage_ >= 59)
    {
        return Distance::DE_28_CM;
    }
    if (voltage_ >= 58)
    {
        return Distance::DE_29_CM;
    }
    if (voltage_ >= 56)
    {
        return Distance::DE_30_CM;
    }
    if (voltage_ >= 55)
    {
        return Distance::DE_31_CM;
    }
    if (voltage_ >= 53)
    {
        return Distance::DE_33_CM;
    }
    if (voltage_ >= 51)
    {
        return Distance::DE_34_CM;
    }
    if (voltage_ >= 50)
    {
        return Distance::DE_35_CM;
    }
    if (voltage_ >= 49)
    {
        return Distance::DE_36_CM;
    }
    if (voltage_ >= 48)
    {
        return Distance::DE_38_CM;
    }
    if (voltage_ >= 47)
    {
        return Distance::DE_37_CM;
    }
    if (voltage_ >= 45)
    {
        return Distance::DE_39_CM;
    }
    if (voltage_ >= 44)
    {
        return Distance::DE_40_CM;
    }
    if (voltage_ >= 43)
    {
        return Distance::DE_42_CM;
    }
    if (voltage_ >= 40)
    {
        return Distance::DE_43_CM;
    }
    if (voltage_ >= 39)
    {
        return Distance::DE_44_CM;
    }
    if (voltage_ >= 38)
    {
        return Distance::DE_45_CM;
    }
    if (voltage_ >= 37)
    {
        return Distance::DE_46_CM;
    }
    if (voltage_ >= 36)
    {
        return Distance::DE_47_CM;
    }
    if (voltage_ >= 34)
    {
        return Distance::DE_48_CM;
    }
    if (voltage_ >= 33)
    {
        return Distance::DE_49_CM;
    }
    if (voltage_ >= 32)
    {
        return Distance::DE_51_CM;
    }
    if (voltage_ >= 30)
    {
        return Distance::DE_52_CM;
    }
    if (voltage_ >= 29)
    {
        return Distance::DE_53_CM;
    }
    if (voltage_ >= 28)
    {
        return Distance::DE_54_CM;
    }
    if (voltage_ >= 27)
    {
        return Distance::DE_55_CM;
    }
    if (voltage_ >= 25)
    {
        return Distance::DE_56_CM;
    }
    if (voltage_ >= 23)
    {
        return Distance::DE_57_CM;
    }
    if (voltage_ >= 22)
    {
        return Distance::DE_58_CM;
    }
    if (voltage_ >= 21)
    {
        return Distance::DE_60_CM;
    }
    if (voltage_ >= 19)
    {
        return Distance::DE_61_CM;
    }
    if (voltage_ >= 17)
    {
        return Distance::DE_62_CM;
    }
    if (voltage_ >= 16)
    {
        return Distance::DE_63_CM;
    }
    if (voltage_ >= 15)
    {
        return Distance::DE_64_CM;
    }
    if (voltage_ >= 13)
    {
        return Distance::DE_66_CM;
    }
    if (voltage_ >= 11)
    {
        return Distance::DE_67_CM;
    }
    if (voltage_ >= 9)
    {
        return Distance::DE_68_CM;
    }
    if (voltage_ >= 8)
    {
        return Distance::DE_69_CM;
    }
    if (voltage_ >= 7)
    {
        return Distance::DE_70_CM;
    }
    else
    {
        return Distance::INCONNU;
    }
}

uint8_t GestionnaireDistance::determineDistancePourLePoteau()
{
    calibrerDistance();

    if (voltage_ >= 158)
    {
        return Distance::DE_5_CM;
    }
    if (voltage_ >= 148)
    {
        return Distance::DE_6_CM;
    }
    if (voltage_ >= 136)
    {
        return Distance::DE_7_CM;
    }
    if (voltage_ >= 122)
    {
        return Distance::DE_8_CM;
    }
    if (voltage_ >= 112)
    {
        return Distance::DE_9_CM;
    }
    if (voltage_ >= 101)
    {
        return Distance::DE_10_CM;
    }
    if (voltage_ >= 95)
    {
        return Distance::DE_11_CM;
    }
    if (voltage_ >= 91)
    {
        return Distance::DE_12_CM;
    }
    if (voltage_ >= 86)
    {
        return Distance::DE_13_CM;
    }
    if (voltage_ >= 82)
    {
        return Distance::DE_14_CM;
    }
    if (voltage_ >= 79)
    {
        return Distance::DE_15_CM;
    }
    if (voltage_ >= 77)
    {
        return Distance::DE_16_CM;
    }
    if (voltage_ >= 73)
    {
        return Distance::DE_17_CM;
    }
    if (voltage_ >= 70)
    {
        return Distance::DE_18_CM;
    }
    if (voltage_ >= 68)
    {
        return Distance::DE_19_CM;
    }
    if (voltage_ >= 67)
    {
        return Distance::DE_20_CM;
    }
    if (voltage_ >= 63)
    {
        return Distance::DE_21_CM;
    }
    if (voltage_ >= 62)
    {
        return Distance::DE_22_CM;
    }
    if (voltage_ >= 60)
    {
        return Distance::DE_23_CM;
    }
    if (voltage_ >= 59)
    {
        return Distance::DE_24_CM;
    }
    if (voltage_ >= 57)
    {
        return Distance::DE_25_CM;
    }
    if (voltage_ >= 54)
    {
        return Distance::DE_26_CM;
    }
    if (voltage_ >= 53)
    {
        return Distance::DE_27_CM;
    }
    if (voltage_ >= 52)
    {
        return Distance::DE_30_CM;
    }
    if (voltage_ >= 51)
    {
        return Distance::DE_29_CM;
    }
    if (voltage_ >= 49)
    {
        return Distance::DE_31_CM;
    }
    if (voltage_ >= 47)
    {
        return Distance::DE_33_CM;
    }
    if (voltage_ >= 45)
    {
        return Distance::DE_35_CM;
    }
    if (voltage_ >= 42)
    {
        return Distance::DE_37_CM;
    }
    if (voltage_ >= 41)
    {
        return Distance::DE_38_CM;
    }
    if (voltage_ >= 40)
    {
        return Distance::DE_39_CM;
    }
    if (voltage_ >= 39)
    {
        return Distance::DE_40_CM;
    }
    if (voltage_ >= 37)
    {
        return Distance::DE_41_CM;
    }
    if (voltage_ >= 36)
    {
        return Distance::DE_44_CM;
    }
    if (voltage_ >= 34)
    {
        return Distance::DE_45_CM;
    }
    if (voltage_ >= 32)
    {
        return Distance::DE_46_CM;
    }
    if (voltage_ >= 30)
    {
        return Distance::DE_47_CM;
    }
    if (voltage_ >= 29)
    {
        return Distance::DE_49_CM;
    }
    if (voltage_ >= 28)
    {
        return Distance::DE_50_CM;
    }
    if (voltage_ >= 26)
    {
        return Distance::DE_51_CM;
    }
    if (voltage_ >= 24)
    {
        return Distance::DE_53_CM;
    }
    if (voltage_ >= 22)
    {
        return Distance::DE_54_CM;
    }
    if (voltage_ >= 20)
    {
        return Distance::DE_55_CM;
    }
    if (voltage_ >= 18)
    {
        return Distance::DE_57_CM;
    }
    if (voltage_ >= 15)
    {
        return Distance::DE_58_CM;
    }
    if (voltage_ >= 14)
    {
        return Distance::DE_59_CM;
    }
    if (voltage_ >= 12)
    {
        return Distance::DE_60_CM;
    }
    if (voltage_ >= 11)
    {
        return Distance::DE_61_CM;
    }
    if (voltage_ >= 10)
    {
        return Distance::DE_62_CM;
    }
    if (voltage_ >= 8)
    {
        return Distance::DE_63_CM;
    }
    if (voltage_ >= 6)
    {
        return Distance::DE_64_CM;
    }
    if (voltage_ >= 4)
    {
        return Distance::DE_65_CM;
    }
    else
    {
        return Distance::INCONNU;
    }
}
