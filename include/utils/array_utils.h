#ifndef SYMMFEA_ARRAY_UTILS_H
#define SYMMFEA_ARRAY_UTILS_H

#include "Eigen/Dense"
#include "vector"
template <typename T>
Eigen::Array<unsigned long, Eigen::Dynamic, 1> argsort(Eigen::Array<T, Eigen::Dynamic, 1> arr)
{
    Eigen::Array<unsigned long, Eigen::Dynamic, 1> indices(arr.size());
    for (unsigned long i = 0; i < arr.size(); ++i)
    {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [&](unsigned long i, unsigned long j)
              { return arr(i) < arr(j); });

    return indices;
}

template <typename T>
// sort in ascending order (higher rank means higher values)
Eigen::Array<unsigned long, Eigen::Dynamic, 1> rank(Eigen::Array<T, Eigen::Dynamic, 1> arr)
{
    return argsort<unsigned long>(argsort<T>(arr));
}

#endif // SYMMFEA_ARRAY_UTILS_H
