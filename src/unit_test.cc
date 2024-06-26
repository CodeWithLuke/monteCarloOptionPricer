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

// TODO: seeding failing on github build machine, fix this to have proper unit tests below
// TEST(UnitTest, RandomNumberGenerator)
// {
//     GaussianRNG g_rng = GaussianRNG(0.0, 1.0, 0);
//     EXPECT_NEAR (g_rng.getRandomNumber(), 0.30280521512031555, 1e-6);
// }

TEST(UnitTest, AssetRandomWalk)
{
    auto today = date::sys_days{floor<date::days>(std::chrono::system_clock::now())};
    auto expiry = date::sys_days{floor<date::days>(std::chrono::system_clock::now() + date::years {1})};
    EXPECT_NO_THROW(simulate_asset_random_walk(100.0, today, expiry, 0.15, 0.30));
}

TEST(UnitTest, MonteCarloRandomWalk)
{
    auto today = date::sys_days{floor<date::days>(std::chrono::system_clock::now())};
    auto expiry = date::sys_days{floor<date::days>(std::chrono::system_clock::now() + date::years {1})};

    EXPECT_NO_THROW(calc_monte_carlo_random_walk(100000, 100.0, today, expiry, 0.15, 0.30));
}
