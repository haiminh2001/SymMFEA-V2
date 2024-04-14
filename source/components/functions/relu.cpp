#include "components/functions/relu.h"

ArrayXf Relu::_forward(std::stack <ArrayXf>& X){
    auto x = X.top();
    X.pop();

    auto result = x.array().max(0);

    this->inputDelta.clear();
    // Use select to create an array where values are 1.0 where x > 0, and 0 otherwise
    this->inputDelta.push_back((x.array() > 0).select(ArrayXf::Ones(x.size()), ArrayXf::Zero(x.size())));
    return result;
}


Relu::Relu() : Node(1) {
    this->symbol = "Relu";
}

Node* Relu::clone(){
    Relu* new_node = new Relu();
    return new_node;
}