#ifndef SYMMFEA_ARRAY_UTILS_H
#define SYMMFEA_ARRAY_UTILS_H

#include "Eigen/Dense"
#include "vector"
#include <fstream>
#include <sstream>

namespace ArrayUtils
{
    template <typename T>
    Eigen::Array<unsigned long, Eigen::Dynamic, 1> argsort(Eigen::Array<T, Eigen::Dynamic, 1> arr);

    template <typename T>
    Eigen::Array<unsigned long, Eigen::Dynamic, 1> rank(Eigen::Array<T, Eigen::Dynamic, 1> arr);

    template <typename T>
    unsigned long argmax(Eigen::Array<T, Eigen::Dynamic, 1> arr);

    Eigen::ArrayXXf readCSV(const std::string &filename, bool has_header = true);
}

#endif // SYMMFEA_ARRAY_UTILS_H
