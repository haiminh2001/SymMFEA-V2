#include <vector>
#include "components/functions/sum.h"

ArrayXf Sum::_forward(std::stack<ArrayXf> &X)
{
    ArrayXf result = X.top();
    X.pop();

    auto num_operands = this->arity - 1;
    while (num_operands > 0)
    {
        result = result + X.top();
        X.pop();
        num_operands--;
    }

    this->inputDelta = std::vector<ArrayXf>(this->arity, ArrayXf(result.size()));

    for (auto vec : this->inputDelta)
        vec.setOnes();
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