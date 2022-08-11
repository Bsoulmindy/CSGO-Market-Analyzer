#include "console.hpp"
#include <iostream>
#include "audio.hpp"

void show_offer(Weapon_Skin_Wear const &wear)
{
    play_audio("../audio/notification.wav");
    for (auto const &offer : wear.get_offers())
    {
        std::cout << "Price: " << offer.get_price() << std::endl;
        std::cout << "URL: "
                  << "www.steamcommunity.com/market/listings/730/" << wear.get_link() << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
    }
}

void show_profitable_combination(Combination &combination)
{
    std::cout << "Inputs: " << std::endl;
    for (auto input : combination.get_inputs())
    {
        std::cout << "\t" << input.get_weapon_skin_wear().get_link() << std::endl;
    }
    std::cout << "Outputs: " << std::endl;
    for (auto output : combination.get_outputs())
    {
        std::cout << "\t" << output.get_weapon_skin_wear().get_link() << std::endl;
    }
    std::cout << "Profit margin: " << combination.get_profit_margin() << std::endl;
    std::cout << "Money lost in worst case: " << combination.get_money_lost_in_worst_case() << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

void show_usage()
{
    std::cout << "Usage: <program> [mode]" << std::endl;
    std::cout << "<mode> can be : " << std::endl;
    std::cout << "-search [seconds] : Searching for offers, and retry each [seconds]" << std::endl;
    std::cout << "-profit [start_id] [end_id_excluded]: Determines profits in collections/cases between [start_id] and [end_id] (Useful when you want to save the process of profitation, because it's very slow" << std::endl;
}

void show_determining_current_skin_profitation(Weapon_Skin const &skin, std::string collection_case_name)
{
    std::cout << "Determining profit for : " << collection_case_name << " : " << skin.get_name() << std::endl;
}

void show_computing_price(Weapon_Skin const &skin, std::string collection_case_name)
{
    std::cout << "Computing price for : " << collection_case_name << " : " << skin.get_name() << std::endl;
}

void show_searching_offers(Weapon_Skin_Wear const &wear)
{
    std::cout << "Searching offers for : " << wear.get_link() << std::endl;
}

void show_retrying_searching_offers(int secondes)
{
    std::cout << "Searching finished. Retrying in " << secondes << " secondes" << std::endl;
}