#include <boost/test/unit_test.hpp>
#include "../src/model/database.hpp"

BOOST_AUTO_TEST_SUITE(Database)

BOOST_AUTO_TEST_CASE(Getting_Hierarchy_Collection)
{
    BOOST_CHECK_NO_THROW(initialize_collections_and_cases());
}

BOOST_AUTO_TEST_CASE(Getting_Profitations)
{
    Weapon_Skin_Wear wear(5, (Wear)0, "");
    BOOST_CHECK_NO_THROW(get_profitation_of_wear(wear));
}

BOOST_AUTO_TEST_CASE(Insert_Combination_and_Deleting)
{
    Weapon_Skin_Wear wear(2, (Wear)0);
    Interval interval(0.45f, 0.5f);
    Combination_Input input(wear, 0.0f, interval);
    std::list<Combination_Output> outputs;
    outputs.push_back(Combination_Output((Weapon_Skin_Wear(5, (Wear)1)), 5.0f));
    outputs.push_back(Combination_Output((Weapon_Skin_Wear(6, (Wear)1)), 6.0f));
    Combination combination(input, outputs, 0.0f, 0.0f);
    BOOST_REQUIRE_NO_THROW(save_combination(combination));
    BOOST_CHECK_NO_THROW(combination_rollback());
}

BOOST_AUTO_TEST_SUITE_END()