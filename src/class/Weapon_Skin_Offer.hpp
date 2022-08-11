#ifndef WEAPON_SKIN_OFFER_HPP_INCLUDED
#define WEAPON_SKIN_OFFER_HPP_INCLUDED

class Weapon_Skin_Offer
{
public:
    Weapon_Skin_Offer(long id, float price, float wear);
    bool operator<(const Weapon_Skin_Offer &other) const;
    long get_id() const;
    float get_price() const;
    float get_wear() const;

private:
    long m_id;
    float m_price;
    float m_wear;
};

#endif // WEAPON_SKIN_OFFER_HPP_INCLUDED