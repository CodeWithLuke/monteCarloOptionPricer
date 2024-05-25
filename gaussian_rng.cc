#include "gaussian_rng.hpp"
#include <random>


GaussianRNG::GaussianRNG(float mean, float stddev) :
m_mean { mean }, m_stddev { stddev } 
{
    // Create a random number generator
    std::random_device rd;  // Seed generator
    std::mt19937 m_gen(rd()); // Mersenne Twister engine

    // Create a normal (Gaussian) distribution
    std::normal_distribution<> m_generator(mean, stddev);
}

GaussianRNG::GaussianRNG(float mean, float stddev, int seed) :
m_mean { mean }, m_stddev { stddev }, m_seed { seed }
{
    // Create a random number generator
    std::mt19937 m_gen(seed); // Mersenne Twister engine

    // Create a normal (Gaussian) distribution
    std::normal_distribution<> m_generator(mean, stddev);
}

float GaussianRNG::getRandomNumber() {
    return m_generator(m_gen);
}

