#include <iostream>
#include <chrono>
#include <date/date.h>
#include <date/tz.h>
#include "gaussian_rng.hpp"
#include "add.h"

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(UnitTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);

    auto test_date = date::sys_days{ date::year{2023}/5/21};

    auto future_date = test_date + date::days{100};
    EXPECT_EQ (date::year_month_day{future_date}.month(), date::month(8));

    EXPECT_EQ(add(2,3), 5);
}

TEST(UnitTest, RandomNumberGenerator)
{
    GaussianRNG g_rng = GaussianRNG(0.0, 1.0);
    EXPECT_NO_THROW(g_rng.getRandomNumber());
}

