#include "Weapon_Skin.hpp"

Weapon_Skin::Weapon_Skin(int id, std::string name, float min_wear, float max_wear)
    : m_id(id), m_name(name), m_min_wear(min_wear), m_max_wear(max_wear), m_wears(std::set<Weapon_Skin_Wear>())
{
}

void Weapon_Skin::add_wear(const Weapon_Skin_Wear &wear)
{
    m_wears.insert(wear);
}

int Weapon_Skin::get_id() const
{
    return m_id;
}

std::set<Weapon_Skin_Wear> Weapon_Skin::get_wears() const
{
    return m_wears;
}

float Weapon_Skin::get_min_wear() const
{
    return m_min_wear;
}

float Weapon_Skin::get_max_wear() const
{
    return m_max_wear;
}

std::string Weapon_Skin::get_name() const
{
    return m_name;
}

int Weapon_Skin::remove_wear(const Weapon_Skin_Wear &wear)
{
    return m_wears.erase(wear);
}