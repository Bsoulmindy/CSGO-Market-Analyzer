#ifndef WEAR_INFO_HPP
#define WEAR_INFO_HPP
#include "Interval.hpp"
#include "Weapon_Skin_Wear.hpp"

class Wear_Info
{
public:
    Wear_Info(int id, Wear wear, Interval interval, float actual_price);
    Wear_Info(Interval interval, float actual_price);
    int get_id() const;
    Interval get_interval() const;
    float get_actual_price() const;
    bool operator<(const Wear_Info &other) const;
    Wear get_wear() const;

private:
    int m_id;
    Wear m_wear;
    Interval m_wear_interval;
    float m_actual_price;
};

#endif