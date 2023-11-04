#include <random>
#include <algorithm>
#include <chrono>
#include "components/DataUtils/utils.h"

std::vector <long> rand_perm(long size){
    std::vector<long> indices(size);

    // Fill the indices with consecutive numbers
    for (long i = 0; i < size; ++i) {
        indices[i] = i;
    }
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));

    return indices;
}

