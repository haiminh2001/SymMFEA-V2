#ifndef SYMMFEA_ARRAY_UTILS_H
#define SYMMFEA_ARRAY_UTILS_H

#include "Eigen/Dense"
#include "vector"

template <typename T>
std::vector<Eigen::Index> argsort(Eigen::Array<T, Eigen::Dynamic, 1> arr)
{
    std::vector<Eigen::Index> indices(arr.size());
    for (Eigen::Index i = 0; i < arr.size(); ++i)
    {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [&arr](Eigen::Index i, Eigen::Index j)
              { return arr[i] < arr[j]; });
    return indices;
}


#endif // SYMMFEA_ARRAY_UTILS_H
