#ifndef COLLECTION_HPP_INCLUDED
#define COLLECTION_HPP_INCLUDED

#include "Weapon_Skin_Rarity.hpp"
#include "Collection_Case.hpp"

class Collection : public Collection_Case
{
public:
    Collection(int id, std::string name);
};

#endif // COLLECTION_HPP_INCLUDED