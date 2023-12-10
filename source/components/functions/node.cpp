#include "components/functions/node.h"

std::vector<ArrayXf> matrix_vector_row_wise_production(ArrayXXf M, ArrayXf v)
{
    std::vector<ArrayXf> result;

    for (int i = 0; i < M.rows(); ++i)
    {
        result.push_back(M.row(i) * v);
    }
    return result;
}

Node::Node(int arity, int index)
{
    this->arity = arity;
    this->index = index;
}

Node::Node(int arity)
{
    this->arity = arity;
    this->index = -1;
}

bool Node::is_leaf()
{
    return this->arity == 0;
}

ArrayXf Node::eval(ArrayXXf X)
{
    assert(this->index >= 0);
    assert(this->is_leaf());
    auto result = X.col(this->index);
    this->weightDelta = result;
    return result;
}

std::vector<ArrayXf> Node::backprop(ArrayXf &dY)
{
    auto delta = (this->weightDelta * dY).mean();
    if (this->is_leaf())
        return std::vector<ArrayXf>();
    else
    {
        auto derivativeSignals = matrix_vector_row_wise_production(this->inputDelta, dY);

        assert(derivativeSignals.size() == this->arity);

        return derivativeSignals;
    }
}

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << "Node type: " << node.symbol << " | Node arity: " << node.arity << std::endl;
    return os;
}
