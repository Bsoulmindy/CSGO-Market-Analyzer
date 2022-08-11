#ifndef WEAPON_SKIN_HPP_INCLUDED
#define WEAPON_SKIN_HPP_INCLUDED

#include <string>
#include <set>
#include "Weapon_Skin_Wear.hpp"

class Weapon_Skin
{
public:
    Weapon_Skin(int id, std::string name, float min_wear, float max_wear);
    void add_wear(const Weapon_Skin_Wear &wear);
    int get_id() const;
    float get_min_wear() const;
    float get_max_wear() const;
    std::set<Weapon_Skin_Wear> get_wears() const;
    std::string get_name() const;
    int remove_wear(const Weapon_Skin_Wear &wear);

private:
    int m_id;
    float m_min_wear;
    float m_max_wear;
    std::string m_name;
    std::set<Weapon_Skin_Wear> m_wears;
};

#endif // WEAPON_SKIN_HPP_INCLUDED