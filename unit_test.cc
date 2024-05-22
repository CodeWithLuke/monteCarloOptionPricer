#include <iostream>
#include <chrono>
#include <date/date.h>
#include <date/tz.h>
#include "add.h"

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(UnitTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);

    auto today = date::floor<date::days>(date::clock_cast_detail::system_clock::now());

    auto future_date = today + date::days{100};
    EXPECT_EQ (date::year_month_day{future_date}.month(), date::month(8));

    EXPECT_EQ(add(2,3), 5);
}

