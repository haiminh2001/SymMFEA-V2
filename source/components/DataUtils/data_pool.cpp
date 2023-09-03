#include "data_pool.h"
#include <random>
#include <algorithm>
#include <chrono>
#include "Eigen/Core"
#include <cmath>

#include <iostream>
std::vector <long> rand_perm(long size){
    std::vector<long> indices(size);

    // Fill the indices with consecutive numbers
    for (long i = 0; i < size; ++i) {
        indices[i] = i;
    }
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));

    return indices;
}

DataPool::DataPool(ArrayXXf& X, ArrayXf& y, float test_size=0.2){
    long n_datapoints = X.rows();
    //shuffle
    std::vector <long> indices = rand_perm(n_datapoints);
    auto _X = ArrayXXf(n_datapoints, X.cols());
    auto _y = ArrayXf(n_datapoints);

    for (long i = 0; i < n_datapoints; ++i){
        long index = indices[i];
        _X.row(index) = X.row(index);
        _y.row(index) = y.row(index);
    }
    
    long size = (long) std::lround(test_size * n_datapoints);

    this->X_train = _X(Eigen::seq(0, size - 1), Eigen::all);
    this->X_val = _X(Eigen::seq(size, n_datapoints - 1), Eigen::all);
    this->y_train = _y(Eigen::seq(0, size - 1));
    this->y_val = _y(Eigen::seq(size, n_datapoints - 1));
}