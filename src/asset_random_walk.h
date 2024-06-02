#include <map>

#include <date/date.h>

std::map <date::sys_days, float> simulate_asset_random_walk_full_path(
    float s_0, date::sys_days start_date, date::sys_days end_date, 
    float drift, float volatility
);

float simulate_asset_random_walk(
    float s_0, date::sys_days start_date, date::sys_days end_date, 
    float drift, float volatility);

void parallel_random_walk(
    int partial_n, float s_0, date::sys_days start_date, date::sys_days end_date, 
    float drift, float volatility, std::vector<float>& result, std::mutex& result_mutex);

float average(std::vector<float> const& v);

float calc_monte_carlo_random_walk(int n, float s_0, date::sys_days start_date, date::sys_days end_date,
    float drift, float volatility);