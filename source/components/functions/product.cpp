#include "product.h"
#include <vector>
ArrayXXf Product::eval(std::vector <ArrayXXf> X){
    assert (X.size() == 2);
    return X[0] * X[1];
}
