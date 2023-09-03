#include <vector>
#include "sum.h"

using Eigen::ArrayXXf;

ArrayXXf Sum::eval(std::vector <ArrayXXf> X){
    ArrayXXf result = X[0];
    auto num_operands = X.size();
    for (int i = 1; i < num_operands; ++i){
        result = result + X[i];
    }
    return result;
};