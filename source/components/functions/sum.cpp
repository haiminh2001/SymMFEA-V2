#include <Eigen/Dense>
#include <vector>
#include "sum.h"
#include <numeric>

using Eigen::MatrixXf;

MatrixXf Sum::eval(std::vector <MatrixXf> X){
//    return std::accumulate(X.begin(), X.end(), Eigen::MatrixXf::Zero(),
//                                          [](const Eigen::MatrixXf& a, const Eigen::MatrixXf& b) {
//                                              return a + b;
//                                          });
    return X[0] + X[1];
};