#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <list>
#include "../class/Collection.hpp"
#include "../class/Case.hpp"
#include "../class/Combination.hpp"
#include "../class/Wear_Info.hpp"

std::list<Collection_Case> initialize_collections_and_cases();
void get_rarities_of_collection_case(Collection_Case &collection);
void get_rarities_of_case(Case &case_skins);
void get_skins_of_rarity(Weapon_Skin_Rarity &rarity);
void get_wears_of_skin(Weapon_Skin &skin);
void save_combination(Combination const &combination);
std::list<Wear_Info> get_profitation_of_wear(Weapon_Skin_Wear &wear);
static void combination_rollback(int id_combination);
void combination_rollback();
std::list<Weapon_Skin_Wear> get_all_profitable_wears();
Collection_Case get_collection_case(int id);
Weapon_Skin_Wear find_by_id(int id);
int check_if_combination_outputs_are_the_same(Combination &combination);
void insert_input_in_combination(int id_combination, Combination_Input combination_input);

#endif