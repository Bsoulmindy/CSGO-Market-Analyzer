#include <boost/test/unit_test.hpp>
#include "../src/controller/profiter.hpp"
#include "../src/controller/searcher.hpp"

BOOST_AUTO_TEST_SUITE(Controller)

BOOST_AUTO_TEST_CASE(Searching_Profitations)
{
    determine_profitation(1, 2);
}

BOOST_AUTO_TEST_CASE(Searching_Offers)
{
    search_offers();
}

BOOST_AUTO_TEST_SUITE_END()