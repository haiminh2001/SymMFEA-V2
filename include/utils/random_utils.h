#ifndef SYMMFEA_RANDOM_UTILS_H
#define SYMMFEA_RANDOM_UTILS_H

#include <random>

//NOTE: may be use eigen random instead
template <typename  T>
T randint(T min, T max){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rng);
}


#endif //SYMMFEA_RANDOM_UTILS_H

