#include "components/functions/product.h"

ArrayXf Product::_eval(std::stack <ArrayXf>& X){
    
    auto x1 = X.top();
    X.pop();
    auto x2 = X.top();
    X.pop();

    this->inputDelta.clear();
    this->inputDelta.push_back(this->weight() * x2);
    this->inputDelta.push_back(this->weight() * x1);
    return x1 * x2;
}


Product::Product() : Node(2) {
    this->symbol = "*";
}
Node* Product::clone(){
    Product* new_node = new Product();
    return new_node;
}