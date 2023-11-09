#include "components/functions/product.h"

ArrayXf Product::eval(std::stack <ArrayXf>& X){
    auto x1 = X.top();
    X.pop();
    auto x2 = X.top();
    X.pop();
    return x1 * x2;
}


Product::Product() : Node(2) {
    this->symbol = "*";
}
Node* Product::clone(){
    Product* new_node = new Product();
    return new_node;
}