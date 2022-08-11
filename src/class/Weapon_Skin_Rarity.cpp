#include "Weapon_Skin_Rarity.hpp"

Weapon_Skin_Rarity::Weapon_Skin_Rarity(int id, Rarity rarity)
    : m_id(id), m_rarity(rarity), m_skins(std::list<Weapon_Skin>())
{
}

bool Weapon_Skin_Rarity::operator<(const Weapon_Skin_Rarity &other) const
{
    return m_rarity > other.m_rarity;
}

void Weapon_Skin_Rarity::add_skin(const Weapon_Skin &skin)
{
    m_skins.push_back(skin);
}

int Weapon_Skin_Rarity::get_id() const
{
    return m_id;
}

std::list<Weapon_Skin> Weapon_Skin_Rarity::get_skins() const
{
    return m_skins;
}

Rarity Weapon_Skin_Rarity::get_rarity() const
{
    return m_rarity;
}