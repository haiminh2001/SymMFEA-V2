#ifndef SYMMFEA_DATA_VIEW_H
#define SYMMFEA_DATA_VIEW_H
#include "data_pool.h"
#include <vector>
#include <Eigen/Dense>

using Eigen::ArrayXf;
using Eigen::ArrayXXf;

class DataView
{
private:
    DataPool *dataPool;
    std::vector<long> train_indices;
    std::vector<long> val_indices;

public:
    DataView(DataPool *dataPool, float sample);
    DataView();
    ArrayXXf X_train();
    ArrayXXf X_val();
    ArrayXf y_train();
    ArrayXf y_val();
};
#endif // SYMMFEA_DATA_VIEW_H
