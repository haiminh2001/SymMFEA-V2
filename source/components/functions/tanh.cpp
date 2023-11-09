#include "components/functions/tanh.h"

ArrayXf Tanh::eval(std::stack <ArrayXf>& X){
    auto x = X.top();
    X.pop();
    return x.array().tanh();
}


Tanh::Tanh() : Node(1) {
    this->symbol = "Tanh";
}

Node* Tanh::clone(){
    Tanh* new_node = new Tanh();
    return new_node;
}