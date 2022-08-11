#include "searcher.hpp"
#include "../class/Collection.hpp"
#include "../model/database.hpp"
#include "../model/internet.hpp"
#include "../view/console.hpp"
#include <iostream>

void search_offers(int seconds)
{
    while (true)
        for (Weapon_Skin_Wear wear : get_all_profitable_wears())
        {
            show_searching_offers(wear);
            bool isFinished = false;
            while (!isFinished)
                try
                {
                    get_offers(wear);
                    isFinished = true;
                }
                catch (const std::exception &e)
                {
                    sleep(1);
                    continue;
                }

            if (wear.get_offers().size() > 0)
            {
                show_offer(wear);
            }
        }
    show_retrying_searching_offers(seconds);
    sleep(seconds);
}