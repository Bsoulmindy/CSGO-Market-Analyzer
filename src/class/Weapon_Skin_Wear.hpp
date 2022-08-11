#ifndef WEAPON_SKIN_WEAR_HPP_INCLUDED
#define WEAPON_SKIN_WEAR_HPP_INCLUDED

#include <string>
#include <set>
#include "Weapon_Skin_Offer.hpp"

enum Wear
{
    FACTORY_NEW,
    MINIMAL_WEAR,
    FIELD_TESTED,
    WELL_WORN,
    BATTLE_SCARRED
};

class Weapon_Skin_Wear
{
public:
    Weapon_Skin_Wear(int id, Wear wear, std::string link);
    Weapon_Skin_Wear(int id, Wear wear);
    bool operator<(const Weapon_Skin_Wear &other) const;
    void add_offer(const Weapon_Skin_Offer &offer);
    std::string get_link() const;
    void set_actual_price(int price);
    int get_id() const;
    Wear get_wear() const;
    int get_actual_price() const;
    std::set<Weapon_Skin_Offer> get_offers() const;

private:
    int m_id;
    int m_actual_price;
    Wear m_wear;
    std::string m_link;
    std::set<Weapon_Skin_Offer> m_offers;
};

#endif // WEAPON_SKIN_WEAR_HPP_INCLUDED