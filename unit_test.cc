#include <iostream>
#include <chrono>
#include <date/date.h>
#include <date/tz.h>
#include <chrono>
#include "gaussian_rng.hpp"
#include "add.h"
#include "asset_random_walk.h"

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
    GaussianRNG g_rng = GaussianRNG(0.0, 1.0, 0);
    EXPECT_NEAR (g_rng.getRandomNumber(), -0.14638178050518036, 1e-6);
}

// TODO: add actual values for below tests and not just no_throw
TEST(UnitTest, AssetRandomWalk)
{
    auto today = floor<date::days>(std::chrono::system_clock::now());
    auto expiry = floor<date::days>(std::chrono::system_clock::now() + date::years {1});
    EXPECT_EQ(simulate_asset_random_walk(100.0, today, expiry, 0.15, 0.30), 0.0);
}

// TODO: add actual values for below tests and not just no_throw
TEST(UnitTest, MonteCarloRandomWalk)
{
    auto today = floor<date::days>(std::chrono::system_clock::now());
    auto expiry = floor<date::days>(std::chrono::system_clock::now() + date::years {1});

    EXPECT_EQ(monte_carlo_random_walk(10000, 100.0, today, expiry, 0.15, 0.30), 0.0);
}
