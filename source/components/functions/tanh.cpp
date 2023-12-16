#include "components/functions/tanh.h"

ArrayXf Tanh::_eval(std::stack <ArrayXf>& X){
    auto x = X.top();
    X.pop();
    auto result = x.array().tanh();
    this->inputDelta.clear();

    this->inputDelta.push_back(1 - result * result);
    return result;
}


Tanh::Tanh() : Node(1) {
    this->symbol = "Tanh";
}

Node* Tanh::clone(){
    Tanh* new_node = new Tanh();
    return new_node;
}