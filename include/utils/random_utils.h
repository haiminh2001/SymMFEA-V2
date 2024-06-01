#ifndef SYMMFEA_RANDOM_UTILS_H
#define SYMMFEA_RANDOM_UTILS_H
#include <vector>

#include <random>
#include <cassert>

namespace Random
{
    /// @brief random an interger, in range [min, max]
    /// @tparam T 
    /// @param min 
    /// @param max 
    /// @return 
    template <typename T>
    T randint(T min, T max)
    {
        assert(max >= min);
        if (max == min)
            return max;

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    }

    template <typename T>
    T randnorm(T mean, T std_dev)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::normal_distribution<T> dist(mean, std_dev);
        return dist(rng);
    }

    template <typename T>
    T random_choice(const std::vector<float> &probabilities)
    {

        std::random_device rd;
        std::mt19937 gen(rd());

        std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());

        return static_cast<T>(dist(gen));
    }
}

#endif // SYMMFEA_RANDOM_UTILS_H
