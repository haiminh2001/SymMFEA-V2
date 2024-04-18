#include "utils/random_utils.h"
#include <random>
#include <cassert>

namespace Random
{
    template int randint<int>(int min, int max);
    template uint64_t randint<uint64_t>(uint64_t min, uint64_t max);
    template <typename T>
    T randint(T min, T max)
    {
        assert(max >= min);
        if (max == min) return max;
        
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    }

    template float randnorm<float>(float mean, float std_dev);
    template <typename T>
    T randnorm(T mean, T std_dev){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::normal_distribution<T> dist(mean, std_dev);
        return dist(rng);
    }
}