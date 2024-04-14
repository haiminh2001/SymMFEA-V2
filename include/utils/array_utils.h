#ifndef SYMMFEA_ARRAY_UTILS_H
#define SYMMFEA_ARRAY_UTILS_H

#include "Eigen/Dense"
#include "vector"
#include <fstream>
#include <sstream>

namespace ArrayUtils
{
    /// @brief 
    /// @tparam T 
    /// @param arr 
    /// @return return the index of the array after sort in ascending order 
    template <typename T>
    Eigen::Array<uint64_t, Eigen::Dynamic, 1> argsort(Eigen::Array<T, Eigen::Dynamic, 1> arr);

    template <typename T>
    /// sort in ascending order (higher rank means higher values)
    Eigen::Array<uint64_t, Eigen::Dynamic, 1> rank(Eigen::Array<T, Eigen::Dynamic, 1> arr);

    template <typename T>
    uint64_t argmax(Eigen::Array<T, Eigen::Dynamic, 1> arr);

    Eigen::ArrayXXf readCSV(const std::string &filename, bool has_header = true);

    template <typename T>
    T** allocateMatrix(uint32_t num_rows, uint32_t num_columns);
}

#endif // SYMMFEA_ARRAY_UTILS_H
