#include "components/functions/tanh.h"

ArrayXf Tanh::_forward(std::stack<ArrayXf> &X, bool record_gradient)
{
    auto x = X.top();
    X.pop();
    auto result = x.array().tanh();
    if (record_gradient)
    {
        this->inputDelta.clear();
        this->inputDelta.push_back(1 - (result * result));
    }
    return result;
}

Tanh::Tanh() : Node(1)
{
    this->symbol = "Tanh";
}

Node *Tanh::clone()
{
    Tanh *new_node = new Tanh();
    return new_node;
}