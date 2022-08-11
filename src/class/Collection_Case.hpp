#ifndef COLLECTION_CASE_HPP_INCLUDED
#define COLLECTION_CASE_HPP_INCLUDED

#include <string>
#include <set>
#include "Weapon_Skin_Rarity.hpp"

class Collection_Case
{
public:
    Collection_Case(int id, std::string name);
    void add_rarity(const Weapon_Skin_Rarity &rarity);
    int get_id() const;
    std::set<Weapon_Skin_Rarity> get_rarities() const;
    std::string get_name() const;

protected:
    int m_id;
    std::string m_name;
    std::set<Weapon_Skin_Rarity> m_rarities;
};

#endif // COLLECTION_CASE_HPP_INCLUDED