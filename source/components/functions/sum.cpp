#include <vector>
#include "sum.h"

using Eigen::ArrayXXf;

ArrayXXf Sum::eval(std::vector <ArrayXXf> X){
    ArrayXXf result = X[0];
    for (int i = 1; i < X.size(); ++i){
        result = result + X[i];
    }
    return result;
};