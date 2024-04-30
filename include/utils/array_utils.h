#ifndef SYMMFEA_ARRAY_UTILS_H
#define SYMMFEA_ARRAY_UTILS_H

#include "Eigen/Dense"
#include "vector"
#include <fstream>
#include <sstream>

namespace ArrayUtils
{

    template <typename T>
    Eigen::Array<uint64_t, Eigen::Dynamic, 1> argsort(Eigen::Array<T, Eigen::Dynamic, 1> arr)
    {
        Eigen::Array<uint64_t, Eigen::Dynamic, 1> indices(arr.size());
        for (uint64_t i = 0; i < arr.size(); ++i)
        {
            indices[i] = i;
        }

        std::sort(indices.begin(), indices.end(), [&](uint64_t i, uint64_t j)
                  { return arr(i) < arr(j); });

        return indices;
    }

    template <typename T>
    // sort in ascending order (higher rank means higher values)
    Eigen::Array<uint64_t, Eigen::Dynamic, 1> rank(Eigen::Array<T, Eigen::Dynamic, 1> arr)
    {
        return argsort<uint64_t>(argsort<T>(arr));
    }

    Eigen::ArrayXXf readCSV(const std::string &filename, bool has_header = true);

    template <typename T>
    uint64_t argmax(Eigen::Array<T, Eigen::Dynamic, 1> arr)
    {

        uint64_t max_indice = 0;
        T max_value = std::numeric_limits<T>::min();

        for (uint64_t indice = 0; indice < arr.size(); indice++)
        {
            auto val = arr(indice);
            if (val > max_value)
            {
                max_value = val;
                max_indice = indice;
            }
        }
        return max_indice;
    }

    template <typename T>
    T **allocateMatrix(uint32_t num_rows, uint32_t num_columns)
    {
        if (num_rows <= 0 || num_columns <= 0)
        {
            return nullptr; // Handle invalid dimensions
        }

        // Allocate memory for the array of pointers to rows
        T **matrix = (T **)malloc(num_rows * sizeof(T *));
        if (matrix == nullptr)
        {
            return nullptr; // Handle allocation failure
        }
        for (int i = 0; i < num_rows; i++)
        {
            matrix[i] = (T *)malloc(num_columns * sizeof(T));
            if (matrix[i] == nullptr)
            {
                // Free previously allocated rows if allocation fails for a row
                for (int j = 0; j < i; j++)
                {
                    free(matrix[j]);
                }
                free(matrix);
                return nullptr; // Handle allocation failure within loop
            }
        }

        return matrix;
    }
}

#endif // SYMMFEA_ARRAY_UTILS_H