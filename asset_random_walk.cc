#include <map>

#include <mutex>

#include <thread>

#include <math.h>

#include <date/date.h>

#include "gaussian_rng.hpp"

std::map <date::year_month_day, float> simulate_asset_random_walk_full_path(
    float s_0, date::year_month_day start_date, date::year_month_day end_date, 
    float drift, float volatility)
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
    float drift, float volatility)
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

        // business day fraction of the year
        float t = 1.0/252.0;

        ds = drift * t + g_rng.getRandomNumber()*volatility*sqrt(t);

        s *= (1 + ds);

        iter_date += date::days{1};
    }

    return s;

}

void parallel_random_walk(
    int partial_n, float s_0, date::year_month_day start_date, date::year_month_day end_date, 
    float drift, float volatility, std::vector<float>& result, std::mutex& result_mutex) 
{
    for (int i = 0; i < partial_n; i++){
        float partialResult = simulate_asset_random_walk(s_0,  start_date,  end_date, drift, volatility);
        std::lock_guard<std::mutex> lock(result_mutex); // Ensure thread-safe access to the result
        result.push_back(partialResult);
    }
}

float average(std::vector<float> const& v){
    if(v.empty()){
        return 0;
    }

    auto const count = static_cast<float>(v.size());
    return std::reduce(v.begin(), v.end()) / count;
}

float monte_carlo_random_walk(int n, float s_0, date::year_month_day start_date, date::year_month_day end_date,
    float drift, float volatility) 
{
    const int numThreads = 8;

    const int partial_n = (n + numThreads - 1) / numThreads;

    std::vector<std::thread> threads;
    std::vector<float> results; // Array to store the results
    std::mutex result_mutex;

    for (int i_thread = 0; i_thread < numThreads; ++i_thread) {
        threads.emplace_back(
            parallel_random_walk, partial_n, s_0, start_date, end_date, drift, volatility, std::ref(results), std::ref(result_mutex)
        );
    }

        // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
    
    return average(results);

}