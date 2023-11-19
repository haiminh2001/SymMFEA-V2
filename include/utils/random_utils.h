#ifndef SYMMFEA_RANDOM_UTILS_H
#define SYMMFEA_RANDOM_UTILS_H

#include <random>

// NOTE: may be use eigen random instead
namespace Random
{
    
    // min and max are inclusive
    template <typename T>
    T randint(T min, T max);
}

#endif // SYMMFEA_RANDOM_UTILS_H
