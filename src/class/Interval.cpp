#include "Interval.hpp"
#include <stdexcept>

Interval::Interval(float min, float max) : m_min(min), m_max(max)
{
}

float Interval::get_min() const
{
    return m_min;
}

float Interval::get_max() const
{
    return m_max;
}

Interval operator+(const Interval &interval, float value)
{
    return Interval(interval.get_min() + value, interval.get_max() + value);
}

Interval operator-(const Interval &interval, float value)
{
    if ((interval.get_min() - value) <= (interval.get_max() - value))
        return Interval(interval.get_min() - value, interval.get_max() - value);
    else
        return Interval(interval.get_max() - value, interval.get_min() - value);
}

Interval operator*(const Interval &interval, float value)
{
    if (value >= 0)
        return Interval(interval.get_min() * value, interval.get_max() * value);
    else
        return Interval(interval.get_max() * value, interval.get_min() * value);
}

Interval operator/(const Interval &interval, float value)
{
    if (value == 0)
        throw std::invalid_argument("Division by zero");
    else if (value > 0)
        return Interval(interval.get_min() / value, interval.get_max() / value);
    else
        return Interval(interval.get_max() / value, interval.get_min() / value);
}

Interval operator+(const Interval &interval, const Interval &other)
{
    return Interval(interval.get_min() + other.get_min(), interval.get_max() + other.get_max());
}

Interval operator-(const Interval &interval, const Interval &other)
{
    if ((interval.get_min() - other.get_max()) <= (interval.get_max() - other.get_min()))
        return Interval(interval.get_min() - other.get_max(), interval.get_max() - other.get_min());
    else
        return Interval(interval.get_max() - other.get_min(), interval.get_min() - other.get_max());
}

Interval Interval::operator/(const Interval &other)
{
    float min = std::max(m_min, other.get_min());
    float max = std::min(m_max, other.get_max());
    if (min > max)
    {
        return Interval(0, 0);
    }
    return Interval(min, max);
}

bool Interval::isEmpty() const
{
    if (m_min > m_max)
        throw std::runtime_error("The bound of interval are not correct");
    return m_min == m_max;
}