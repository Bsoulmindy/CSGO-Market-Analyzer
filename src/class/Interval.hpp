#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class Interval
{
public:
    Interval(float min, float max);
    float get_min() const;
    float get_max() const;
    bool isEmpty() const;
    Interval operator/(const Interval &other);

private:
    float m_min;
    float m_max;
};

Interval operator+(const Interval &interval, float value);
Interval operator-(const Interval &interval, float value);
Interval operator*(const Interval &interval, float value);
Interval operator/(const Interval &interval, float value);
Interval operator+(const Interval &interval, const Interval &other);
Interval operator-(const Interval &interval, const Interval &other);

#endif