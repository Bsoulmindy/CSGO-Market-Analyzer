#include "Combination_Input.hpp"

Combination_Input::Combination_Input(Weapon_Skin_Wear weapon_skin_wear, float price_max, Interval wear_interval)
    : m_weapon_skin_wear(weapon_skin_wear),
      m_price_max(price_max),
      m_wear_interval(wear_interval)
{
}

Weapon_Skin_Wear Combination_Input::get_weapon_skin_wear() const
{
  return m_weapon_skin_wear;
}

float Combination_Input::get_price_max() const
{
  return m_price_max;
}

Interval Combination_Input::get_wear_interval() const
{
  return m_wear_interval;
}