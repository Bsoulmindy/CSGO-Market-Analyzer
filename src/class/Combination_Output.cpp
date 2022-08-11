#include "Combination_Output.hpp"

Combination_Output::Combination_Output(Weapon_Skin_Wear weapon_skin_wear, float actual_price)
    : m_weapon_skin_wear(weapon_skin_wear), m_actual_price(actual_price)
{
}

Weapon_Skin_Wear Combination_Output::get_weapon_skin_wear() const
{
    return m_weapon_skin_wear;
}

float Combination_Output::get_actual_price() const
{
    return m_actual_price;
}