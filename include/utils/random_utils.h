#ifndef SYMMFEA_RANDOM_UTILS_H
#define SYMMFEA_RANDOM_UTILS_H


namespace Random
{
    
    // min and max are inclusive
    template <typename T>
    T randint(T min, T max);

    template <typename T>
    T randnorm(T mean, T std_dev);

}

#endif // SYMMFEA_RANDOM_UTILS_H
