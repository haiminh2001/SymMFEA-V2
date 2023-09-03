#include "product.h"

ArrayXf Product::eval(std::stack <ArrayXf>& X){
    auto x1 = X.top();
    X.pop();
    auto x2 = X.top();
    X.pop();
    return x1 * x2;
}
