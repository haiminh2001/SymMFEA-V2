#ifndef SYMMFEA_RANDOM_UTILS_H
#define SYMMFEA_RANDOM_UTILS_H
#include <vector>
namespace Random
{

    // min and max are inclusive
    template <typename T>
    T randint(T min, T max);

    template <typename T>
    T randnorm(T mean, T std_dev);

    /// @brief return a random indice from the given probabilities
    /// @tparam T 
    /// @param probabilities 
    /// @return 
    template <typename T>
    T random_choice(const std::vector<float> &probabilities);
    
}

#endif // SYMMFEA_RANDOM_UTILS_H
