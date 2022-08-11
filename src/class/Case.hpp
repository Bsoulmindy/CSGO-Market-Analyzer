#ifndef CASE_HPP_INCLUDED
#define CASE_HPP_INCLUDED

#include "Weapon_Skin_Rarity.hpp"
#include "Collection_Case.hpp"

class Case : public Collection_Case
{
public:
    Case(int id, std::string name);
};

#endif // CASE_HPP_INCLUDED