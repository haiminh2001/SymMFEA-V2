#include "utils/array_utils.h"
#include <limits>

namespace ArrayUtils
{

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

}
