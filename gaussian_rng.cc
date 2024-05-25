#include "gaussian_rng.hpp"
#include <random>


GaussianRNG::GaussianRNG(float mean, float stddev) :
m_mean { mean }, m_stddev { stddev } 
{}

GaussianRNG::GaussianRNG(float mean, float stddev, int seed) :
m_mean { mean }, m_stddev { stddev }, m_seed { seed }
{}

float GaussianRNG::getRandomNumber() {
    static std::random_device rd;
    static std::mt19937 eng(rd()); // seed the generator
    std::normal_distribution<> distr(m_mean, m_stddev);
    return distr(eng);
}

