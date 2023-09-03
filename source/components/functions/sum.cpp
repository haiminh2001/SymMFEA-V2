#include <vector>
#include "sum.h"

using Eigen::MatrixXf;

MatrixXf Sum::eval(std::vector <MatrixXf> X){
    MatrixXf result = X[0];
    for (int i = 1; i < X.size(); ++i){
        result = result + X[i];
    }
    return result;
};