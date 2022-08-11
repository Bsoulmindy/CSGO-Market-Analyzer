#ifndef COMBINATION_OUTPUT_HPP
#define COMBINATION_OUTPUT_HPP
#include "Weapon_Skin_Wear.hpp"

class Combination_Output
{
public:
    Combination_Output(Weapon_Skin_Wear weapon_skin_wear, float actual_price);
    Weapon_Skin_Wear get_weapon_skin_wear() const;
    float get_actual_price() const;

private:
    Weapon_Skin_Wear m_weapon_skin_wear;
    float m_actual_price;
};

#endif