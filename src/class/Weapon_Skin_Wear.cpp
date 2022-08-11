#include "Weapon_Skin_Wear.hpp"

Weapon_Skin_Wear::Weapon_Skin_Wear(int id, Wear wear, std::string link)
    : m_id(id), m_wear(wear), m_link(link), m_actual_price(0), m_offers(std::set<Weapon_Skin_Offer>())
{
}

Weapon_Skin_Wear::Weapon_Skin_Wear(int id, Wear wear)
    : m_id(id), m_wear(wear), m_link(""), m_actual_price(0), m_offers(std::set<Weapon_Skin_Offer>())
{
}

bool Weapon_Skin_Wear::operator<(const Weapon_Skin_Wear &other) const
{
    return m_wear < other.m_wear;
}

void Weapon_Skin_Wear::add_offer(const Weapon_Skin_Offer &offer)
{
    m_offers.insert(offer);
}

std::string Weapon_Skin_Wear::get_link() const
{
    return m_link;
}

void Weapon_Skin_Wear::set_actual_price(int price)
{
    m_actual_price = price;
}

int Weapon_Skin_Wear::get_id() const
{
    return m_id;
}

Wear Weapon_Skin_Wear::get_wear() const
{
    return m_wear;
}

int Weapon_Skin_Wear::get_actual_price() const
{
    return m_actual_price;
}

std::set<Weapon_Skin_Offer> Weapon_Skin_Wear::get_offers() const
{
    return m_offers;
}