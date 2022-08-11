#ifndef WEAPON_SKIN_RARITY_HPP_INCLUDED
#define WEAPON_SKIN_RARITY_HPP_INCLUDED

#include <stdint.h>
#include <list>
#include "Weapon_Skin.hpp"

enum Rarity : int
{
    CONSUMER_GRADE,
    INDUSTRIAL_GRADE,
    MIL_SPEC,
    RESTRICTED,
    CLASSIFIED,
    COVERT,
    CONTRABAND
};

class Weapon_Skin_Rarity
{
public:
    Weapon_Skin_Rarity(int id, Rarity rarity);
    bool operator<(const Weapon_Skin_Rarity &other) const;
    void add_skin(const Weapon_Skin &skin);
    int get_id() const;
    std::list<Weapon_Skin> get_skins() const;
    Rarity get_rarity() const;

private:
    int m_id;
    Rarity m_rarity;
    std::list<Weapon_Skin> m_skins;
};

#endif