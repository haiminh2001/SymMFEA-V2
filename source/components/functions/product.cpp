#include "components/functions/product.h"

ArrayXf Product::_forward(std::stack <ArrayXf>& X){
    //the second input is actually on top    
    auto x2 = X.top();
    X.pop();
    auto x1 = X.top();
    X.pop();

    this->inputDelta.clear();
    //derivative over the first input
    this->inputDelta.push_back(x2);
    //derivative over the second input
    this->inputDelta.push_back(x1);
    return x1 * x2;
}


Product::Product() : Node(2) {
    this->symbol = "*";
}
Node* Product::clone(){
    Product* new_node = new Product();
    return new_node;
}