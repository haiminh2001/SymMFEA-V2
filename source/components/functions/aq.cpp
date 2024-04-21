#include "components/functions/aq.h"

ArrayXf Aq::_forward(std::stack<ArrayXf> &X, bool record_gradient)
{
    auto x2 = X.top();
    X.pop();

    auto x1 = X.top();
    X.pop();

    auto result = x1 / (x2 * x2 + 1).sqrt();



    if (record_gradient)
    {
        this->inputDelta.clear();

        auto dx1 = 1 / (x2 * x2 + 1).sqrt();
        
        auto dx2 = - x2 * x1 / (x2 * x2 + 1).pow(1.5);
        
        this->inputDelta.push_back(dx1);
        this->inputDelta.push_back(dx2);
    }
    return result;
}

Aq::Aq() : Node(2)
{
    this->symbol = "/";
}

Node *Aq::clone()
{
    Aq *new_node = new Aq();
    return new_node;
}