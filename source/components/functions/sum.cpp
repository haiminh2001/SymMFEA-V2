#include <vector>
#include "components/functions/sum.h"

ArrayXf Sum::_forward(std::stack<ArrayXf> &X, bool record_gradient)
{
    ArrayXf result = X.top();
    X.pop();

    auto num_remaining_operands = this->arity - 1;
    while (num_remaining_operands > 0)
    {
        result = result + X.top();
        X.pop();
        num_remaining_operands--;
    }

    if (record_gradient)
    {
        this->inputDelta = std::vector<ArrayXf>(this->arity, ArrayXf::Ones(result.size()));
    }

    return result;
}

Sum::Sum(int arity) : Node(arity)
{
    this->symbol = "+";
}

Node *Sum::clone()
{
    Sum *new_node = new Sum(this->arity);
    return new_node;
}