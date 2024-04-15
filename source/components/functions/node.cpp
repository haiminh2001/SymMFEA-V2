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

std::vector<ArrayXf> Node::backprop(ArrayXf &dY)
{
    auto nodeWeight = this->weight();
    auto delta = (this->weightDelta * dY).mean() * nodeWeight;

    IndividualInfos::weightDelta(this->central_id, this->id) = delta;

    if (this->is_leaf())
        return std::vector<ArrayXf>();
    else
    {
        auto derivativeSignals = matrix_vector_row_wise_production(this->inputDelta, dY * nodeWeight);

        assert(derivativeSignals.size() == this->arity);

        return derivativeSignals;
    }
}

template ArrayXf Node::forward<ArrayXXf>(ArrayXXf X, bool record_gradient = true);
template ArrayXf Node::forward<std::stack<ArrayXf> &>(std::stack<ArrayXf> &X, bool record_gradient = true);

/// @brief
/// @tparam T
/// @param X
/// @return calculate the output of the node and record the weight delta
template <typename T>
ArrayXf Node::forward(T X, bool record_gradient)
{
    auto result = this->_forward(X, record_gradient);
    if (record_gradient)
        this->weightDelta = result;
    return result * this->weight();
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