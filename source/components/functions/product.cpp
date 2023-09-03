#include "product.h"
#include <vector>
#include <iostream>
ArrayXXf Product::eval(std::vector <ArrayXXf> X){
    assert (X.size() == 2);
    std::cout<<X[0]<<std::endl;
    std::cout<<X[1]<<std::endl;
    return X[0] * X[1];
}
