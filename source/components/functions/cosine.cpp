#include "components/functions/cosine.h"

ArrayXf Cosine::_forward(std::stack<ArrayXf> &X, bool record_gradient)
{
    auto x = X.top();
    X.pop();

    auto result = x.array().cos();

    if (record_gradient)
    {
        this->inputDelta.clear();
        this->inputDelta.push_back(-x.array().sin());
    }
    return result;
}

Cosine::Cosine() : Node(1)
{
    this->symbol = "cos";
}

Node *Cosine::clone()
{
    Cosine *new_node = new Cosine();
    return new_node;
}