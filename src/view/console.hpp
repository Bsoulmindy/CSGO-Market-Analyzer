#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "../class/Weapon_Skin.hpp"
#include "../class/Combination.hpp"

void show_offer(Weapon_Skin_Wear const &wear);
void show_profitable_combination(Combination &combination);
void show_usage();
void show_determining_current_skin_profitation(Weapon_Skin const &skin, std::string collection_case_name);
void show_computing_price(Weapon_Skin const &skin, std::string collection_case_name);
void show_searching_offers(Weapon_Skin_Wear const &wear);
void show_retrying_searching_offers(int secondes);

#endif