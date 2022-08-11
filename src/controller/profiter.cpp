#include "profiter.hpp"
#include "../model/database.hpp"
#include "../class/Wear_Info.hpp"
#include "../model/internet.hpp"
#include <algorithm>
#include "../class/Combination.hpp"
#include "../view/console.hpp"
#include <iostream>

float get_max_wear_of_wear(Wear wear)
{
    switch (wear)
    {
    case Wear::FACTORY_NEW:
        return 0.07f;
    case Wear::MINIMAL_WEAR:
        return 0.15f;
    case Wear::FIELD_TESTED:
        return 0.38f;
    case Wear::WELL_WORN:
        return 0.45f;
    case Wear::BATTLE_SCARRED:
        return 1.0f;
    }
    throw std::runtime_error("Unknown wear");
}

float get_min_wear_of_wear(Wear wear)
{
    switch (wear)
    {
    case Wear::FACTORY_NEW:
        return 0.0f;
    case Wear::MINIMAL_WEAR:
        return 0.07f;
    case Wear::FIELD_TESTED:
        return 0.15f;
    case Wear::WELL_WORN:
        return 0.38f;
    case Wear::BATTLE_SCARRED:
        return 0.45f;
    }
    throw std::runtime_error("Unknown wear");
}

void determine_profit(Weapon_Skin_Wear &wear_actual, std::list<std::set<Wear_Info>> &list_wear_infos, float min_skin_wear, float max_skin_wear)
{
    float min_wear = std::max(get_min_wear_of_wear(wear_actual.get_wear()), min_skin_wear);
    float max_wear = std::min(get_max_wear_of_wear(wear_actual.get_wear()), max_skin_wear);
    Interval wear_actual_interval = Interval(min_wear, max_wear);

    // Initialization
    std::list<std::set<Wear_Info>> list_wear_infos_intersected;
    std::set<float> wear_limits;
    for (std::set<Wear_Info> const &skin_wears : list_wear_infos)
    {
        std::set<Wear_Info> wear_infos_intersected;
        for (Wear_Info const &info : skin_wears)
        {
            Interval wear_intersected = wear_actual_interval / info.get_interval();
            if (!wear_intersected.isEmpty())
            {
                wear_limits.insert(wear_intersected.get_max());
                Wear_Info new_info = Wear_Info(info.get_id(), info.get_wear(), wear_intersected, info.get_actual_price());
                wear_infos_intersected.insert(new_info);
            }
        }
        list_wear_infos_intersected.push_back(wear_infos_intersected);
    }

    // Deducing all combinations possibles
    std::list<Combination> combinations;
    float wear_min = get_min_wear_of_wear(wear_actual.get_wear());
    for (float limit : wear_limits)
    {
        std::list<Combination_Output> outputs;
        for (std::set<Wear_Info> const &skin_wears : list_wear_infos_intersected)
        {
            for (Wear_Info const &info : skin_wears)
            {
                if (info.get_interval().get_max() >= limit)
                {
                    Weapon_Skin_Wear wear = find_by_id(info.get_id());
                    Combination_Output output = Combination_Output(wear, info.get_actual_price());
                    outputs.push_back(output);
                    break;
                }
            }
        }

        // Checking if the combination is worhy
        float price_median = 0.0f;
        for (Combination_Output const &output : outputs)
        {
            price_median += output.get_actual_price();
        }
        price_median /= outputs.size();
        // If worthy, add it to the list of combinations
        if (wear_actual.get_actual_price() / (10 * 0.85) + 0.02 < price_median)
        {
            float price_max = (price_median - 0.02) / (10 / 0.85);
            Interval wear_interval = Interval(wear_min, limit);
            Combination_Input input = Combination_Input(wear_actual, price_max, wear_interval);

            float profit_margin = price_median - (wear_actual.get_actual_price() / 10 / 0.85 + 0.02);
            float min_price = 0.0f;
            for (Combination_Output const &output : outputs)
            {
                if (min_price > output.get_actual_price() || min_price == 0.0f)
                {
                    min_price = output.get_actual_price();
                }
            }
            float money_lost_in_worst_case = (wear_actual.get_actual_price() / 10 / 0.85 + 0.02) - min_price;
            if (money_lost_in_worst_case < 0)
                money_lost_in_worst_case = 0;

            Combination combination = Combination(input, outputs, profit_margin, money_lost_in_worst_case);
            combinations.push_back(combination);
            show_profitable_combination(combination);
        }
        wear_min = limit;
    }

    // save the combination in the database
    for (Combination &combination : combinations)
    {
        // Check if there's already a combination with the same outputs
        int id = check_if_combination_outputs_are_the_same(combination);
        if (id == 0)
            save_combination(combination);
        else
        {
            for (Combination_Input input : combination.get_inputs())
            {
                insert_input_in_combination(id, input);
            }
        }
    }
}

void determine_profitation(int min, int max)
{
    for (int i = min; i < max; i++)
    {
        Collection_Case const &collection_case = get_collection_case(i);
        bool first_rarity = true;
        std::list<std::set<Wear_Info>> list_wear_infos;
        std::map<int, int> map_id_price_wear;
        for (Weapon_Skin_Rarity const &rarity : collection_case.get_rarities())
        {
            if (!first_rarity)
            {
                for (Weapon_Skin &weapon_skin : rarity.get_skins())
                {
                    show_determining_current_skin_profitation(weapon_skin, collection_case.get_name());
                    float min_skin_wear = weapon_skin.get_min_wear();
                    float max_skin_wear = weapon_skin.get_max_wear();
                    std::set<Weapon_Skin_Wear> wears = weapon_skin.get_wears();

                    for (Weapon_Skin_Wear wear : wears)
                    {
                        bool isFinished = false;
                        while (!isFinished)
                            try
                            {
                                get_actual_price(wear);
                                isFinished = true;
                            }
                            catch (const std::exception &e)
                            {
                                sleep(1);
                                continue;
                            }
                        map_id_price_wear.insert(std::pair<int, int>(wear.get_id(), wear.get_actual_price()));
                        determine_profit(wear, list_wear_infos, min_skin_wear, max_skin_wear);
                    }
                }
                list_wear_infos.clear();
            }
            // It is the last rarity?
            if (rarity.get_rarity() == CONSUMER_GRADE)
                continue;
            Weapon_Skin_Rarity dummy(1, (Rarity)(rarity.get_rarity() - 1));
            if (collection_case.get_rarities().count(dummy) == 0)
                continue;

            for (Weapon_Skin const &weapon_skin : rarity.get_skins())
            {
                show_computing_price(weapon_skin, collection_case.get_name());
                float min_skin_wear = weapon_skin.get_min_wear();
                float max_skin_wear = weapon_skin.get_max_wear();
                std::set<Wear_Info> skin_wears;
                for (Weapon_Skin_Wear wear : weapon_skin.get_wears())
                {
                    if (map_id_price_wear.count(wear.get_id()) > 0)
                        wear.set_actual_price(map_id_price_wear.at(wear.get_id()));
                    else if (wear.get_actual_price() == 0)
                    {
                        bool isFinished = false;
                        while (!isFinished)
                            try
                            {
                                get_actual_price(wear);
                                isFinished = true;
                            }
                            catch (const std::exception &e)
                            {
                                sleep(1);
                                continue;
                            }
                    }

                    int id = wear.get_id();
                    Wear wear_enum = wear.get_wear();
                    float actual_price = wear.get_actual_price() / 100.0f;

                    float min_wear_possible = get_min_wear_of_wear(wear_enum);
                    float max_wear_possible = get_max_wear_of_wear(wear_enum);
                    Interval interval = Interval(std::max(min_wear_possible, min_skin_wear), std::min(max_wear_possible, max_skin_wear));
                    Interval interval_search = (interval - min_skin_wear) / (max_skin_wear - min_skin_wear);

                    Wear_Info info = Wear_Info(id, wear_enum, interval_search, actual_price);
                    skin_wears.insert(info);
                }
                list_wear_infos.push_back(skin_wears);
            }
            first_rarity = false;
            map_id_price_wear.clear();
        }
    }
}