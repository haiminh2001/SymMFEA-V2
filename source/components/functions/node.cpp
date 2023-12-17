#include "components/functions/node.h"
#include "central_units/individual_infos.h"
#include "central_units/individual_infos.h"

std::vector<ArrayXf> matrix_vector_row_wise_production(std::vector<ArrayXf> M, ArrayXf v)
{
    std::vector<ArrayXf> result;

    for (int i = 0; i < M.size(); ++i)
    {
        result.push_back(M[i] * v);
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

ArrayXf Node::_eval(ArrayXXf X)
{
    assert(this->index >= 0);
    assert(this->is_leaf());
    auto result = X.col(this->index);
    return result;
}

std::vector<ArrayXf> Node::backprop(ArrayXf &dY)
{
    auto delta = (this->weightDelta * dY).mean();

    IndividualInfos::weightDelta(this->central_id, this->id) = delta;

    if (this->is_leaf())
        return std::vector<ArrayXf>();
    else
    {
        auto derivativeSignals = matrix_vector_row_wise_production(this->inputDelta, dY);

        assert(derivativeSignals.size() == this->arity);

        return derivativeSignals;
    }
}

template ArrayXf Node::eval<ArrayXXf>(ArrayXXf X);
template ArrayXf Node::eval<std::stack<ArrayXf> &>(std::stack<ArrayXf> &X);

template <typename T>
ArrayXf Node::eval(T X)
{
    auto result = this->_eval(X);
    this->weightDelta = result;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << "Node type: " << node.symbol << " | Node arity: " << node.arity << std::endl;
    return os;
}

float Node::weight()
{
    return IndividualInfos::weight(this->central_id, this->id);
}