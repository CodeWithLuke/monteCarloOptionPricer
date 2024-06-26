#ifndef GAUSSIAN_RNG_HPP
#define GAUSSIAN_RNG_HPP

#include <random>
#include <optional>

class GaussianRNG
{
private:
    float m_mean;
    float m_stddev;
    std::optional<int> m_seed;
    std::normal_distribution<> m_generator;
    std::mt19937 m_gen;
    
public:
    GaussianRNG(float mean, float stddev);
    GaussianRNG(float mean, float stddev, int seed);
    float getRandomNumber();
};

#endif