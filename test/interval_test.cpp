#include <boost/test/unit_test.hpp>
#include "../src/class/Interval.hpp"

BOOST_AUTO_TEST_SUITE(Intervals)

BOOST_AUTO_TEST_CASE(Initialization)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval2(3.0f, 4.0f);
    Interval interval3(-2.0f, 3.0f);
    Interval interval4(0.0f, 0.0f);
    BOOST_CHECK_EQUAL(interval1.get_min(), 1.0f);
    BOOST_CHECK_EQUAL(interval1.get_max(), 2.0f);
    BOOST_CHECK_EQUAL(interval2.get_min(), 3.0f);
    BOOST_CHECK_EQUAL(interval2.get_max(), 4.0f);
    BOOST_CHECK_EQUAL(interval3.get_min(), -2.0f);
    BOOST_CHECK_EQUAL(interval3.get_max(), 3.0f);
    BOOST_CHECK(interval4.isEmpty());
}

BOOST_AUTO_TEST_CASE(Sum_with_value)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval2 = interval1 + 3.0f;
    BOOST_CHECK_EQUAL(interval2.get_min(), 4.0f);
    BOOST_CHECK_EQUAL(interval2.get_max(), 5.0f);
}

BOOST_AUTO_TEST_CASE(Substraction_with_value)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval2 = interval1 - 3.0f;
    BOOST_CHECK_EQUAL(interval2.get_min(), -2.0f);
    BOOST_CHECK_EQUAL(interval2.get_max(), -1.0f);
}

BOOST_AUTO_TEST_CASE(Multiplication_with_value)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval2 = interval1 * 2.5f;
    Interval interval3 = interval1 * -2.5f;
    BOOST_CHECK_EQUAL(interval2.get_min(), 2.5f);
    BOOST_CHECK_EQUAL(interval2.get_max(), 5.0f);
    BOOST_CHECK_EQUAL(interval3.get_min(), -5.0f);
    BOOST_CHECK_EQUAL(interval3.get_max(), -2.5f);
}

BOOST_AUTO_TEST_CASE(Division_with_value)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval2 = interval1 / 2.5f;
    Interval interval3 = interval1 / -2.5f;
    BOOST_CHECK_EQUAL(interval2.get_min(), 0.4f);
    BOOST_CHECK_EQUAL(interval2.get_max(), 0.8f);
    BOOST_CHECK_EQUAL(interval3.get_min(), -0.8f);
    BOOST_CHECK_EQUAL(interval3.get_max(), -0.4f);
    BOOST_CHECK_THROW(interval1 / 0.0f, std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Sum_Intervals)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval3(-2.0f, 3.0f);
    Interval interval4 = interval1 + interval3;
    BOOST_CHECK_EQUAL(interval4.get_min(), -1.0f);
    BOOST_CHECK_EQUAL(interval4.get_max(), 5.0f);
}

BOOST_AUTO_TEST_CASE(Substraction_Intervals)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval3(-2.0f, 3.0f);
    Interval interval4 = interval1 - interval3;
    BOOST_CHECK_EQUAL(interval4.get_min(), -2.0f);
    BOOST_CHECK_EQUAL(interval4.get_max(), 4.0f);
}

BOOST_AUTO_TEST_CASE(Intersection_Intervals)
{
    Interval interval1(1.0f, 2.0f);
    Interval interval3(-2.0f, 3.0f);
    Interval interval4 = interval1 / interval3;
    Interval interval5 = interval1 / Interval(-2.0f, 0.0f);
    BOOST_CHECK_EQUAL(interval4.get_min(), 1.0f);
    BOOST_CHECK_EQUAL(interval4.get_max(), 2.0f);
    BOOST_CHECK(interval5.isEmpty());
}

BOOST_AUTO_TEST_SUITE_END()