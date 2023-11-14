#include "components/functions/node.h"

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

ArrayXf Node::eval(ArrayXXf X) const
{
    assert(this->index >= 0);
    return X.col(this->index);
}

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << "Node type: " << node.symbol << " | Node arity: " << node.arity << std::endl;
    return os;
}