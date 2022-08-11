#include "Weapon_Skin_Offer.hpp"

Weapon_Skin_Offer::Weapon_Skin_Offer(long id, float price, float wear)
    : m_id(id), m_price(price), m_wear(wear)
{
}

bool Weapon_Skin_Offer::operator<(const Weapon_Skin_Offer &other) const
{
    return m_wear < other.m_wear;
}

long Weapon_Skin_Offer::get_id() const
{
    return m_id;
}

float Weapon_Skin_Offer::get_price() const
{
    return m_price;
}

float Weapon_Skin_Offer::get_wear() const
{
    return m_wear;
}