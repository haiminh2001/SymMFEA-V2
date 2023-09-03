#ifndef SYMMFEA_DATA_POOL_H
#define SYMMFEA_DATA_POOL_H

#endif //SYMMFEA_DATA_POOL_H
#include <Eigen/Dense>
using Eigen::ArrayXXf;
using Eigen::ArrayXf;

class DataPool{
public:
    DataPool(ArrayXXf &X, ArrayXf &y, float test_size);

    ArrayXXf X_train;
    ArrayXXf X_val;
    ArrayXf y_train;
    ArrayXf y_val;
};