#include <boost/test/unit_test.hpp>
#include "../src/view/audio.hpp"

BOOST_AUTO_TEST_SUITE(Audio)

BOOST_AUTO_TEST_CASE(Testing_audio)
{
    play_audio("../audio/notification.wav");
    std::cout << "Price: "
              << "0.35" << std::endl;
    std::cout << "URL: "
              << "www.steamcommunity.com/market/listings/730/" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()