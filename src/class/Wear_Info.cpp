#include "Wear_Info.hpp"

Wear_Info::Wear_Info(int id, Wear wear, Interval interval, float actual_price)
    : m_id(id), m_wear(wear), m_wear_interval(interval), m_actual_price(actual_price)
{
}

int Wear_Info::get_id() const
{
    return m_id;
}

Interval Wear_Info::get_interval() const
{
    return m_wear_interval;
}

float Wear_Info::get_actual_price() const
{
    return m_actual_price;
}

bool Wear_Info::operator<(const Wear_Info &other) const
{
    return m_wear < other.m_wear;
}

Wear Wear_Info::get_wear() const
{
    return m_wear;
}

Wear_Info::Wear_Info(Interval interval, float actual_price)
    : m_wear_interval(interval), m_actual_price(actual_price)
{
}