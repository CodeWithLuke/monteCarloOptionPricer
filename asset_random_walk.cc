#include <map>

#include <date/date.h>

#include "gaussian_rng.hpp"

std::map <date::year_month_day, float> simulate_asset_random_walk_full_path(
    float s_0, date::year_month_day start_date, date::year_month_day end_date, 
    float drift=0.0, float volatility=1.0)
{

    float ds;

    auto s = s_0;

    auto g_rng = GaussianRNG(0.0, 1.0);

    std::map<date::year_month_day, float> day_price_pairs;

    auto iter_date =  date::sys_days{start_date};

    while(iter_date < end_date) {
        date::weekday wd{iter_date};
        if (wd.c_encoding() == 0 || wd.c_encoding() == 6) {
            iter_date += date::days{1};
            continue;
        }

        day_price_pairs[start_date] = s;

        ds = drift / 252 + g_rng.getRandomNumber()*volatility;

        s *= ds;

        iter_date += date::days{1};

    }

    return day_price_pairs;

}

float simulate_asset_random_walk(
    float s_0, date::year_month_day start_date, date::year_month_day end_date, 
    float drift=0.0, float volatility=1.0)
{

    float ds;

    auto s = s_0;

    auto g_rng = GaussianRNG(0.0, 1.0);

    auto iter_date =  date::sys_days{start_date};

    while(iter_date < end_date) {
        date::weekday wd{iter_date};
        if (wd.c_encoding() == 0 || wd.c_encoding() == 6) {
            iter_date += date::days{1};
            continue;
        }

        ds = drift / 252 + g_rng.getRandomNumber()*volatility;

        s *= ds;
        iter_date += date::days{1};
    }

    return s;

}