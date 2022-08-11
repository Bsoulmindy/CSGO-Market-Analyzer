#include "Collection_Case.hpp"

Collection_Case::Collection_Case(int id, std::string name)
    : m_name(name), m_id(id), m_rarities(std::set<Weapon_Skin_Rarity>())
{
}

void Collection_Case::add_rarity(const Weapon_Skin_Rarity &rarity)
{
    m_rarities.insert(rarity);
}

int Collection_Case::get_id() const
{
    return m_id;
}

std::set<Weapon_Skin_Rarity> Collection_Case::get_rarities() const
{
    return m_rarities;
}

std::string Collection_Case::get_name() const
{
    return m_name;
}