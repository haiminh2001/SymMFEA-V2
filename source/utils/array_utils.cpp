#include "utils/array_utils.h"
#include <limits>
namespace ArrayUtils
{

    template Eigen::Array<uint64_t, Eigen::Dynamic, 1> rank<float>(Eigen::Array<float, Eigen::Dynamic, 1> arr);
    template Eigen::Array<uint64_t, Eigen::Dynamic, 1> argsort<long>(Eigen::Array<long, Eigen::Dynamic, 1> arr);
    template uint64_t argmax<float>(Eigen::Array<float, Eigen::Dynamic, 1> arr);

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

    Eigen::ArrayXXf readCSV(const std::string &filename, bool has_header)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {

            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::vector<std::vector<float>> data;
        std::string line;

        if (has_header)
            std::getline(file, line);

        while (std::getline(file, line))
        {
            std::vector<float> row;
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ','))
            {
                row.push_back(std::stof(cell));
            }
            data.push_back(row);
        }

        const size_t rows = data.size();
        const size_t cols = data[0].size();

        Eigen::ArrayXXf matrix(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                matrix(i, j) = data[i][j];
            }
        }

        return matrix;
    }

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
