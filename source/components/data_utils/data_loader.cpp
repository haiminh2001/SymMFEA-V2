#include "components/data_utils/data_loader.h"
#include <algorithm>

void DataLoader::get_next_batch(ArrayXXf *&X, ArrayXf *&y)
{

    long start = this->pos_ * this->batch_size;

    // if run out of data, return null
    if (start >= this->num_datapoints)
    {
        X = nullptr;
        y = nullptr;
        return;
    }

    uint64_t end = std::min((this->pos_ + 1) * this->batch_size, this->num_datapoints);

    *X = this->X(Eigen::seq(start, end - 1), Eigen::all);
    *y = this->y(Eigen::seq(start, end - 1));

    this->pos_++;
}

DataLoader::DataLoader(ArrayXXf X, ArrayXf y, uint32_t batch_size)
    : X(X),
      y(y),
      batch_size(batch_size),
      num_datapoints(X.rows()),
      pos_(0)
{
    assert(X.rows() == y.rows() && "X and y must have the same number of rows");
}