#include <boost/test/unit_test.hpp>
#include "../src/model/internet.hpp"
#include "../src/model/database.hpp"

BOOST_AUTO_TEST_SUITE(Internet)

BOOST_AUTO_TEST_CASE(Getting_Actual_Price)
{
    Weapon_Skin_Wear wear(5, (Wear)0, "UMP-45%20|%20Full%20Stop%20(Factory%20New)");
    try
    {
        get_actual_price(wear);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    BOOST_REQUIRE_NO_THROW(get_actual_price(wear));
    BOOST_CHECK_NE(wear.get_actual_price(), 0.0f);
}

BOOST_AUTO_TEST_CASE(Getting_Offers)
{
    Weapon_Skin_Wear wear(5, (Wear)0, "UMP-45%20|%20Full%20Stop%20(Factory%20New)");
    Interval interval(0.0f, 0.7f);
    Combination_Input input(wear, 0.39f, interval);
    std::list<Combination_Output> outputs;
    outputs.push_back(Combination_Output((Weapon_Skin_Wear(7, (Wear)1)), 7.0f));
    outputs.push_back(Combination_Output((Weapon_Skin_Wear(6, (Wear)1)), 6.0f));
    Combination combination(input, outputs, 0.0f, 0.0f);
    BOOST_REQUIRE_NO_THROW(save_combination(combination));

    try
    {
        get_offers(wear);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    BOOST_CHECK_NO_THROW(get_offers(wear));

    BOOST_CHECK_NO_THROW(combination_rollback());
}

BOOST_AUTO_TEST_SUITE_END()