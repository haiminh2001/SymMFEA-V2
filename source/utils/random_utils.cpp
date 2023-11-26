#include "utils/random_utils.h"
#include <random>
#include <cassert>

namespace Random
{
    template int randint<int>(int min, int max);
    template unsigned long randint<unsigned long>(unsigned long min, unsigned long max);
    template <typename T>
    T randint(T min, T max)
    {
        assert(max >= min);
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    }
}