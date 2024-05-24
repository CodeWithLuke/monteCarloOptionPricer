#ifndef GAUSSIAN_RNG_HPP
#define GAUSSIAN_RNG_HPP

#include <random>

class GaussianRNG
{
private:
    float m_mean;
    float m_stddev;
    std::normal_distribution<> m_generator;
    std::mt19937 m_gen;
    
public:
    GaussianRNG(float mean, float stddev);
    float getRandomNumber();
};

#endif