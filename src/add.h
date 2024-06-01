#include <chrono>

#include <date/date.h>
#include <date/tz.h>

int add(int a, int b)
{
    return a + b;
}

std::chrono::system_clock::time_point addDays(date::sys_days d, int n)
{
    auto dp = date::floor<date::days>(d) + date::days{n};

    return dp;
}