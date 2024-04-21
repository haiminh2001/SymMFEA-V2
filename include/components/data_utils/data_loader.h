#ifndef SYMMFEA_DATA_LOADER_H
#define SYMMFEA_DATA_LOADER_H

#include <vector>
#include <iterator>
#include <Eigen/Dense>

using Eigen::ArrayXf;
using Eigen::ArrayXXf;

class DataLoader
{
private:
    uint32_t batch_size;
    ArrayXXf X;
    ArrayXf y;
    uint64_t pos_;
    uint64_t num_datapoints;

public:
    DataLoader(ArrayXXf X, ArrayXf y, uint32_t batch_size);

    void get_next_batch(ArrayXXf *&X, ArrayXf *&y);
};
#endif // SYMMFEA_DATA_LOADER_H
