#include <map>

#include <date/date.h>

std::map <date::year_month_day, float> simulate_asset_random_walk_full_path(
    float s_0, date::year_month_day start_date, date::year_month_day end_date, 
    float drift=0.0, float volatility=1.0
);

float simulate_asset_random_walk(
    float s_0, date::year_month_day start_date, date::year_month_day end_date, 
    float drift=0.0, float volatility=1.0);