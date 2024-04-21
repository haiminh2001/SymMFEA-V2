#include "Eigen/Core"
#include <cmath>

#include "components/data_utils/utils.h"
#include "components/data_utils/data_pool.h"


DataPool::DataPool(ArrayXXf& X, ArrayXf& y, float test_size=0.2){
    long n_datapoints = X.rows();

    std::vector <long> indices = rand_perm(n_datapoints);
    long train_size = (long) std::lround((1 - test_size) * n_datapoints);

    std::vector <long> train_indices (indices.begin(), indices.begin() + train_size);
    std::vector <long> val_indices (indices.begin() + train_size, indices.end());

    this->X_train = X(train_indices, Eigen::all);
    this->X_val = X(val_indices, Eigen::all);
    this->y_train = y(train_indices);
    this->y_val = y(val_indices);
}

long DataPool::num_train() {
    return this->X_train.rows();
}

long DataPool::num_val() {
    return this->X_val.rows();
}

