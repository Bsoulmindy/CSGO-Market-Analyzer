#ifndef COMBINATION_INPUT_HPP
#define COMBINATION_INPUT_HPP
#include "Weapon_Skin_Wear.hpp"
#include "Interval.hpp"

class Combination_Input
{
public:
    Combination_Input(Weapon_Skin_Wear weapon_skin_wear, float price_max, Interval wear_interval);
    Weapon_Skin_Wear get_weapon_skin_wear() const;
    float get_price_max() const;
    Interval get_wear_interval() const;

private:
    Weapon_Skin_Wear m_weapon_skin_wear;
    float m_price_max;
    Interval m_wear_interval;
};

#endif